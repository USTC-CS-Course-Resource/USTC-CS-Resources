from worker import *
import multiprocessing


def main():
    queue = multiprocessing.Queue()
    lock = multiprocessing.Lock()
    receiver = multiprocessing.Process(target=receive, args=(queue, lock), kwargs={'handle_timeout': 3})
    responder = multiprocessing.Process(target=respond, args=(queue, lock))
    receiver.start()
    responder.start()
    receiver.join()
    responder.join()


if __name__ == '__main__':
    main()
