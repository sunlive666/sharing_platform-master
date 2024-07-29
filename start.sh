#此脚本用于启动数据共享平台的全部服务程序

#启动守护模块，由于守护模块很重要，避免误杀，建议在/etc/rc.local中配置，以超级用户身份启动
#/myproject/tools/bin/procctl 10 /myproject/tools/bin/checkproc /myproject/log/checkproc.log

#生成气象站点观测数据，程序每分钟运行一次
/myproject/tools/bin/procctl 60 /myproject/idc/bin/crtsurfdata /myproject/idc/ini/stcode.ini /myproject/dataFile/idc/surfdata /myproject/log/idc/crtsurfdata.log csv,xml,json

#清理原始的气象数据文件，0.02天以前的，/myproject/dataFile/idc/surfdata
/myproject/tools/bin/procctl 300 /myproject/tools/bin/deletefiles /myproject/dataFile/idc/surfdata "*.xml,*.json,*csv" 0.02
#清理原始的气象数据文件，0.02天以前的 /myproject/log/idc
/myproject/tools/bin/procctl 300 /myproject/tools/bin/deletefiles /myproject/log/idc "*.log.20*,*.log" 0.02

#清理服务器上的xml文件，0.02天以前，/myproject/myserver/surfdata
/myproject/tools/bin/procctl 300 /myproject/tools/bin/deletefiles /myproject/myserver/surfdata "*.xml" 0.02

#启动文件传输服务器端
/myproject/tools/bin/procctl 10 /myproject/tools/bin/fileserver 5005 /myproject/log/idc/fileserver.log

#启动文件传输模块
#/myproject/tools/bin/procctl 20 /myproject/tools/bin/tcpputfiles /myproject/log/idc/tcpputfiles_surfdata.log "<ip>192.168.19.128</ip><port>5005</port><clientpath>/myproject/dataFile/idc/surfdata</clientpath><ptype>1</ptype><srvpath>/myproject/myserver/surfdata</srvpath><andchild>false</andchild><matchname>*.xml</matchname><timetvl>30</timetvl><timeout>50</timeout><pname>tcpputfiles_surfdata</pname>"

#启动数据入库模块
/myproject/tools/bin/procctl 10 /myproject/tools/bin/xmltodb /myproject/log/idc/xmltodb_vip.log "<connstr>idc/idcpwd@snorcl11g_128</connstr><charset>Simplified Chinese_China.AL32UTF8</charset><inifilename>/myproject/idc/ini/xmltodb.xml</inifilename><xmlpath>/myproject/myserver/surfdata</xmlpath><xmlpathbak>/myproject/myserver/surfdataBak</xmlpathbak><xmlpatherr>/myproject/myserver/surfdataFail</xmlpatherr><timetvl>20</timetvl><timeout>50</timeout><pname>xmltodb_vip</pname>"



