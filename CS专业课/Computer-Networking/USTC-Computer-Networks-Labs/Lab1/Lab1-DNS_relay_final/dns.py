from utils import cprint_header, cprint_question, cprint_answer
from utils import bytes_to_int, bytes_to_bin, bytes_to_binlist
from utils import binlist_to_int, binlist_to_bytes
from utils import int_to_bytes, int_to_binlist


def parse_domain(bmsg: bytes, cur: int):
    qname = []
    while True:
        if bmsg[cur] == bytes_to_int(b'\xc0'):
            cur = bytes_to_int(bmsg[cur: cur + 2]) - bytes_to_int(b'\xc0\x00')
        label_len = bmsg[cur]
        if label_len == 0:
            break
        qname.append(bmsg[cur + 1: cur + label_len + 1].decode())
        cur += label_len + 1
    cur += 1
    return '.'.join(qname), cur


def encode_addr(addr: str) -> bytes:
    split_addr = addr.split('.')
    split_addr = [int(i) for i in split_addr]
    assert len(split_addr) == 4
    bytes_addr = int_to_bytes(split_addr[0]) + int_to_bytes(split_addr[1]) \
                 + int_to_bytes(split_addr[2]) + int_to_bytes(split_addr[3])
    return bytes_addr


def fake_bmsg(bmsg, addr: str = '0.0.0.0'):
    bmsg = bytearray(bmsg)
    header = DNSHeader(bmsg[:12])
    header.qr = 1
    header.ancount = 1  # a response
    header.ra = 1  # recursive available
    header.rcode = 0  # no error

    cprint_header(header)
    assert header.qdcount == 1
    question = DNSQuestion(bmsg, offset=12)
    cprint_question(question)
    # fake an A-type answer
    bmsg += b'\xc0\x0c'  # pointer
    bmsg += b'\x00\x01'  # A type
    bmsg += b'\x00\x01'  # class = IN
    bmsg += b'\x00\x00\x00\x01'  # ttl
    bmsg += b'\x00\x04'  # 4 bytes for ipv4 address
    bmsg += encode_addr(addr)
    assert len(header.bmsg) == 12
    bmsg[:12] = header.bmsg
    return bmsg


def parse_msg(msg, style=None, fore=None, back=None, sep=' ', end='\n', file=None, level='normal'):
    args = {'style': style, 'fore': fore, 'back': back, 'sep': sep, 'end': end, 'file': file, 'level': level}
    msg = bytearray(msg)
    header = DNSHeader(msg[:12])
    cprint_header(header, **args)
    assert header.qdcount == 1
    question = DNSQuestion(msg, offset=12)
    cprint_question(question, **args)
    offset = question.next_offset
    answers = []
    bmsg = header.bmsg[:12] + question.bmsg[12: offset]
    for i in range(header.ancount):
        answer = DNSAnswer(msg, offset)
        # answer.ttl = 5
        answers.append(answer)
        cprint_answer(answer, **args)
        bmsg += answer.bmsg[offset: answer.next_offset]
        offset = answer.next_offset
    bmsg = bmsg + msg[len(bmsg):]
    return bmsg


class DNSHeader:
    def __init__(self, bmsg):
        self.msg = bytes_to_binlist(bmsg)

    @property
    def bmsg(self):
        return binlist_to_bytes(self.msg)

    @property
    def msg_id(self):
        return binlist_to_int(self.msg[:16])

    @msg_id.setter
    def msg_id(self, value):
        if type(value) == bytes:
            assert len(value) <= 4
            value = b'\x00' * (4-len(value)) + value
            value = bytes_to_bin(value, num_bits=16)
        self.msg[:16] = value

    @property
    def qr(self):
        return self.msg[16]

    @qr.setter
    def qr(self, value: int):
        assert value == 1 or value == 0
        self.msg[16] = str(value)

    @property
    def aa(self):
        return int(self.msg[21])

    @aa.setter
    def aa(self, value: int):
        assert value == 1 or value == 0
        self.msg[21] = str(value)

    @property
    def rd(self):
        return int(self.msg[23])

    @property
    def ra(self) -> int:
        return int(self.msg[24])

    @ra.setter
    def ra(self, value: int):
        assert value == 1 or value == 0
        self.msg[24] = str(value)

    @property
    def rcode(self):
        return binlist_to_int(self.msg[28:32])

    @rcode.setter
    def rcode(self, value):
        if type(value) == int:
            self.msg[28:32] = int_to_binlist(value, num_bits=4)

    @property
    def qdcount(self):
        return binlist_to_int(self.msg[32:48])

    @property
    def ancount(self):
        return binlist_to_int(self.msg[48:64])

    @ancount.setter
    def ancount(self, value):
        if type(value) == int:
            self.msg[48:64] = int_to_binlist(value, num_bits=16)


class DNSQuestion:
    def __init__(self, bmsg: bytes, offset: int = 12):
        self.bmsg = bmsg
        self.offset = offset
        self.qname, self.qtype, self.qclass, self.next_offset = self.content()

    def content(self):
        qname, cur = parse_domain(self.bmsg, self.offset)
        qtype = bytes_to_int(self.bmsg[cur: cur + 2])
        qclass = bytes_to_int(self.bmsg[cur + 2: cur + 4])
        cur += 4
        num_bytes = cur
        return qname, qtype, qclass, num_bytes


class DNSResourceRecord:
    def __init__(self):
        ...


class DNSAnswer(DNSResourceRecord):
    def __init__(self, bmsg, offset):
        super(DNSAnswer, self).__init__()
        self.bmsg = bytearray(bmsg)
        self.offset = offset
        assert self.bmsg[self.offset] >= bytes_to_int(b'\xc0')
        self.len_name = 2
        self.next_offset = self.offset + self.len_name + 10 + self.rdlength

    @property
    def name(self):
        name, cur = parse_domain(self.bmsg, self.offset)
        return name

    @property
    def atype(self):
        return bytes_to_int(self.bmsg[self.offset + self.len_name:
                                      self.offset + self.len_name + 2])

    @property
    def aclass(self):
        return bytes_to_int(self.bmsg[self.offset + self.len_name + 2:
                                      self.offset + self.len_name + 4])

    @property
    def ttl(self):
        return bytes_to_int(self.bmsg[self.offset + self.len_name + 4:
                                      self.offset + self.len_name + 8])

    @ttl.setter
    def ttl(self, value):
        self.bmsg[self.offset + self.len_name + 4:
                  self.offset + self.len_name + 8] = int_to_bytes(value, num_bytes=4)

    @property
    def rdlength(self):
        return bytes_to_int(self.bmsg[self.offset + self.len_name + 8:
                                      self.offset + self.len_name + 10])

    @property
    def rdata(self):
        if self.atype == 5:
            return parse_domain(self.bmsg, self.offset + self.len_name + 10)[0]
        elif self.atype == 1:
            # A type
            assert self.rdlength == 4
            addr = self.bmsg[self.offset + self.len_name + 10: self.offset + self.len_name + 14]
            return '.'.join([str(i) for i in addr])
        else:
            return self.bmsg[self.offset + self.len_name + 10:
                             self.offset + self.len_name + 10 + self.rdlength]

    @rdata.setter
    def rdata(self, value: str):
        assert self.atype == 1
        split_addr = value.split('.')
        split_addr = [int(i) for i in split_addr]
        assert len(split_addr) == 4
        bytes_addr = int_to_bytes(split_addr[0]) + int_to_bytes(split_addr[1])\
                     + int_to_bytes(split_addr[2]) + int_to_bytes(split_addr[3])
        self.bmsg[self.offset + self.len_name + 10: self.offset + self.len_name + 14] = bytes_addr
