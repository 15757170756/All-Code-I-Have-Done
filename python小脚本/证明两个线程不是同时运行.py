# https://mp.weixin.qq.com/s?__biz=MzAwOTgzMDk5Ng==&mid=2650834758&idx=1&sn=68b632c9192a463a1440b74fc274ea10&chksm=80adb07db7da396b90a4862c606b0d787790fa975282a79528b8b75b86cb3ad30b33ce73396c&scene=27#wechat_redirect

import logging
import threading
import time
from concurrent.futures import  ThreadPoolExecutor

def thread_function(name):
    logging.info("Thread %s: starting", name)
    time.sleep(2)
    logging.info("Thread %s: finishing", name)

class FakeDatabase:

    def __init__(self):
        self.value = 0

    def update(self, name):
        logging.info("Thread %s: starting updata", name)
        local_copy = self.value
        local_copy += 1
        time.sleep(0.00000000000001)
        self.value = local_copy
        logging.info("Thread %s: finishing updata", name)

if __name__ == "__main__":
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")
    # logging.info("Main   : before creating thread")
    # x = threading.Thread(target=thread_function, args=(1,))
    # logging.info("Main   : before running thread")
    # x.start()
    # logging.info("Main   : wait for the thread to finish")
    # x.join()
    # logging.info("Main   : all done")
    database = FakeDatabase()
    logging.info("Testing updata. Starting value is %d." % database.value)
    with ThreadPoolExecutor(max_workers=2) as executor:
        for i in range(2):
            executor.submit(database.update, i)

    logging.info("Testing updata. Ending value is %d." % database.value)