# 本程序用于停止数据共享平台全部的服务程序

#停止调度程序
killall -9 procctl

#停止其他程序
killall crtsurfdata deletefiles fileserver tcpputfiles xmltodb


sleep 5

killall -9 crtsurfdata deletefiles fileserver tcpputfiles xmltodb
