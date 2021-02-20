import socket
import select
import multiprocessing
import subprocess
from utils import *
from scapy.layers.dns import *
from scapy.fields import *

A = 1
AAAA = 28

addr_dict = {
             'www.google.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             'www.baidu.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             'feed-image.baidu.com.': {'A': '0.0.0.0', 'AAAA': '::0'},
             # 'sp2.baidu.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             # 'www.a.shifen.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             # 'passport.baidu.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             # 'dss0.bdstatic.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             # 'dss1.bdstatic.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             'ss2.baidu.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             'ss3.baidu.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             'www.baidu.com.ctc.': {'A': '127.0.0.1', 'AAAA': '::1'},
             'www.4399.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             'www.test1.com.': {'A': '127.0.0.1', 'AAAA': '::1'},
             'www.bb.ustc.edu.cn.': {'A': '0.0.0.0', 'AAAA': '::1'}, }


def handler(query, addr, timeout=3):
    query = DNS(query)
    if not query.qd:
        return
    answer = query.copy()
    cprint('\tqname: ', query.qd.qname,
           'in?', str(query.qd.qname, encoding='utf-8') in addr_dict, fore='cyan')
    cprint('\tqtype: ', query.qd.qtype, fore='cyan')
    cprint('\tqclass: ', query.qd.qclass, fore='cyan')
    qname = str(query.qd.qname, encoding='utf-8')
    if qname in addr_dict and answer.qd.qtype:
        cprint('spoof answer', fore='red')
        answer.qr = 1
        answer.aa = 1
        answer.ra = 1
        answer.rcode = 0
        answer.ancount = 1
        rrname = qname
        answer.an = DNSRR(rrname=rrname, type=answer.qd.qtype,
                          rclass=answer.qd.qclass, ttl=20)

        if answer.qd.qtype == A:
            answer.an.rdata = addr_dict[rrname]['A']
        if answer.qd.qtype == AAAA:
            answer.an.rdata = addr_dict[rrname]['AAAA']
        if answer.an.rdata == '0.0.0.0' or answer.an.rdata == '::0':
            answer.rcode = 3
        print_an(answer.an, fore='red')
        answer.ancount = 2
        answer.an = answer.an / answer.an
        answer.an[1].rdata = '127.0.0.6'
    else:
        cprint('real answer', fore='green')
        forward_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        query.type=AAAA
        query.qdcount = 2
        query.qd = query.qd / query.qd
        query.qd[1].qname = 'www.4399.com.'
        forward_sock.sendto(bytes(query), ('8.8.8.8', 53))
        forward_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            forward_sock.settimeout(timeout)
            real_data, _ = forward_sock.recvfrom(1024)
        except socket.timeout:
            forward_sock.close()
            cprint('\ttimeout', fore='green')
            return
        finally:
            forward_sock.close()
        answer = DNS(real_data)
        cprint('\trcode{}'.format(type(answer.rcode)), answer.rcode, fore='green')
        if answer.an is not None:
            cprint('\topcode{}'.format(type(answer.opcode)), answer.opcode, fore='green')
            cprint('\trcode{}'.format(type(answer.rcode)), answer.rcode, fore='green')
            print_an(answer.an, fore='green')

    return answer, addr


def respond(queue, lock):
    cprint('responder start!', fore='red')
    while True:
        if queue.empty():
            continue
        with lock:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            try:
                response, addr = queue.get(block=True)
                sock.bind(('127.0.0.1', 53))
                sock.sendto(bytes(response), addr)
                sock.close()
            except Exception:
                sock.close()
            finally:
                sock.close()


def receive(queue, lock, handle_timeout=3):
    cprint('receiver start!', fore='red')
    counter = 0
    while True:
        subprocess.run('ipconfig /flushdns',
                       stdout=subprocess.DEVNULL,
                       stderr=subprocess.STDOUT)
        with lock:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            sock.bind(('127.0.0.1', 53))
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.settimeout(0.1)
            try:
                query, addr = sock.recvfrom(1024)
                cprint('\nrecv query: {} from {}'.format(query, addr), fore='blue')
                sock.close()
                queue.put(handler(query, addr, timeout=handle_timeout), block=True)
            except BlockingIOError:
                print('[BlockingIOError]')
            except socket.timeout:
                counter += 1
                if counter == 10:
                    print('.', end='')
                    counter = 0
            finally:
                sock.close()
