import socket
from dns import fake_bmsg, parse_msg, DNSHeader, DNSQuestion
from utils import cprint, cprint_header, cprint_question
from utils import bytes_to_int
import multiprocessing as mp
from datetime import datetime
import os.path as osp


def forward(msg):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(2)
    real_dns_server = ('223.5.5.5', 53)  # ali dns server
    # real_dns_server = ('8.8.8.8', 53)  # ali dns server
    try:
        sock.sendto(msg, real_dns_server)
        answer, _ = sock.recvfrom(1024)
    except socket.timeout:
        ...
        return None
    return answer


def relay(semaphore: mp.Semaphore, queue: mp.Queue, output_lock: mp.Lock,
          bmsg: bytes, addr: tuple, relay_dict, recv_time: datetime):
    semaphore.acquire()
    bmsg = bytearray(bmsg)
    header = DNSHeader(bmsg[:12])
    header.aa = 1
    bmsg = header.bmsg + bmsg[12:]
    assert header.qdcount == 1
    question = DNSQuestion(bmsg, offset=12)
    with output_lock:
        cprint(f'[{recv_time}][recv query {bytes_to_int(bmsg[:2])}]: {bmsg} from {addr}', fore='green', style='reverse')
        cprint_header(header, fore='green')
        cprint_question(question, fore='green')
    if question.qname in relay_dict:
        if relay_dict[question.qname] == '0.0.0.0':
            header.rcode = 3
            answer = header.bmsg + bmsg[12:]
            mode = 'intercept  '
        elif question.qtype == 1:
            answer = fake_bmsg(bmsg, relay_dict[question.qname])
            mode = 'local resolve '
        else:
            answer = forward(bmsg)
            if answer is None:
                return
            mode = 'relay msg  '
    else:
        answer = forward(bmsg)
        mode = 'relay msg  '
    queue.put((answer, addr, recv_time, mode))
    semaphore.release()


def receiver(queue, socket_lock, output_lock, sock):
    config_path = osp.join(osp.dirname(__file__), 'etc', 'config')
    last_read_config_time = -1
    semaphore = mp.Semaphore(7)
    while True:
        with socket_lock:
            if osp.getmtime(config_path) > last_read_config_time:
                last_read_config_time = osp.getmtime(config_path)
                config_file = open(config_path)
                relay_dict = {}
                for line in config_file:
                    if len(line) == 1 and line[0] == '\n':
                        continue
                    addr, name = line.strip('\n').split(' ')
                    relay_dict[name] = addr
                print(relay_dict)
                config_file.close()
            sock.settimeout(0.1)
            try:
                bmsg, addr = sock.recvfrom(1024)
                mp.Process(target=relay, args=(semaphore, queue, output_lock,
                                               bmsg, addr, relay_dict, datetime.now())).start()
            except socket.timeout:
                ...
            except ConnectionResetError:
                cprint("ConnectionResetError", fore='red')
                ...
            except Exception:
                ...


def backsender(queue: mp.Queue, socket_lock: mp.Lock, output_lock: mp.Lock, sock: socket.socket):
    while True:
        with socket_lock:
            sock.settimeout(5)
            for answer_count in range(queue.qsize()):
                if queue.qsize() <= 0:
                    break
                answer, addr, recv_time, mode = queue.get()
                if answer is None:
                     continue
                with output_lock:
                    cprint(f'[{datetime.now()}][{mode}{bytes_to_int(answer[:2])}]: {answer}', fore='cyan', style='reverse')
                    answer = parse_msg(answer, fore='cyan')
                sock.sendto(answer, addr)
                send_time = datetime.now()
                time_cost = send_time - recv_time
                with output_lock:
                    cprint(f'[{send_time}][time cost  {bytes_to_int(answer[:2])}]: {time_cost}', fore='blue', style='reverse')


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    while True:
        queue = mp.Queue()
        socket_lock = mp.Lock()
        output_lock = mp.Lock()
        receiver_process = mp.Process(target=receiver, args=(queue, socket_lock, output_lock, sock))
        backsender_process = mp.Process(target=backsender, args=(queue, socket_lock, output_lock, sock))
        try:
            sock.bind(('127.0.0.1', 53))
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            receiver_process.start()
            backsender_process.start()
            receiver_process.join()
            backsender_process.join()
            receiver_process.close()
            backsender_process.close()
        finally:
            sock.close()
            receiver_process.close()
            backsender_process.close()


if __name__ == '__main__':
    main()
