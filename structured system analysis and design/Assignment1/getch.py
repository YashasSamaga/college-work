import tty, sys, termios, select
import threading
import time

class _Getch:
    def __init__(self):
        import tty, sys
        fd = sys.stdin.fileno()
        new_term = termios.tcgetattr(fd)
        new_term[3] = (new_term[3] & ~termios.ICANON & ~termios.ECHO)
        termios.tcsetattr(fd, termios.TCSAFLUSH, new_term)

    def __call__(self):
        return sys.stdin.read(1)

class AsyncGetch:
    def __init__(self):
        self._Getch = _Getch()
        self.__keys = []
        self.__lock = threading.Lock()
        self.__thread = threading.Thread(target=self.poll)
        self.__thread.start()
    
    def poll(self):
        while True:
            tmp = self._Getch()
            self.__lock.acquire()
            self.__keys.append(tmp)
            self.__lock.release()

            time.sleep(0.05)

    def getch(self):
        self.__lock.acquire()
        tmp = self.__keys
        self.__keys = []
        self.__lock.release()
        return tmp