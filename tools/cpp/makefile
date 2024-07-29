PUBLIC = /myproject/public/_public.cpp
PUBHOME = -I /myproject/public

##################################################
# oracle头文件路径
ORAINCL = -I$(ORACLE_HOME)/rdbms/public -I/myproject/public/db/oracle

# oracle库文件路径
ORALIB =  -L$(ORACLE_HOME)/lib -L.

# oracle的oci库
ORALIBS = -lclntsh

# 开发框架oracle的cpp文件名，这里直接包含进来，没有采用链接库，是为了方便调试。
ORACPP = /myproject/public/db/oracle/_ooci.cpp
##################################################

all:procctl checkproc deletefiles fileserver tcpputfiles tcpgetfiles xmltodb dminingoracle deletetable migratetable \
	syncref syncinc

procctl:procctl.cpp
	g++ -g -o $@ $^
	cp $@ ../bin/.
checkproc:checkproc.cpp
	g++ -g -o $@ $^ $(PUBLIC) $(PUBHOME)
	cp $@ ../bin/.
deletefiles:deletefiles.cpp
	g++ -g -o $@ $^ $(PUBLIC) $(PUBHOME)
	cp $@ ../bin/.
fileserver:fileserver.cpp
	g++ -g -o $@ $^ $(PUBLIC) $(PUBHOME)
	cp $@ ../bin/.
tcpputfiles:tcpputfiles.cpp
	g++ -g -o $@ $^ $(PUBLIC) $(PUBHOME)
	cp $@ ../bin/.
tcpgetfiles:tcpgetfiles.cpp
	g++ -g -o $@ $^ $(PUBLIC) $(PUBHOME)
	cp $@ ../bin/.
xmltodb:xmltodb.cpp _tools.cpp
	g++ -g -o $@ $^ $(PUBLIC) $(ORACPP) $(ORALIB) $(ORALIBS) $(PUBHOME) $(ORAINCL)
	cp $@ ../bin/.
dminingoracle:dminingoracle.cpp $(ORACPP) $(PUBLIC)
	g++ -g -o $@ $^ $(ORAINCL) $(ORALIB) $(ORALIBS) $(PUBHOME)
	cp $@ ../bin/.
deletetable:deletetable.cpp $(ORACPP) $(PUBLIC)
	g++ -g -o $@ $^ $(ORAINCL) $(ORALIB) $(ORALIBS) $(PUBHOME)
	cp $@ ../bin/.
migratetable:migratetable.cpp _tools.cpp $(ORACPP) $(PUBLIC)
	g++ -g -o $@ $^ $(ORAINCL) $(ORALIB) $(ORALIBS) $(PUBHOME)
	cp $@ ../bin/.	
syncref:syncref.cpp _tools.cpp $(ORACPP) $(PUBLIC)
	g++ -g -o $@ $^ $(ORAINCL) $(ORALIB) $(ORALIBS) $(PUBHOME)
	cp $@ ../bin/.	
syncinc:syncinc.cpp _tools.cpp $(ORACPP) $(PUBLIC)
	g++ -g -o $@ $^ $(ORAINCL) $(ORALIB) $(ORALIBS) $(PUBHOME)
	cp $@ ../bin/.
clean:
	rm -f procctl checkproc deletefiles fileserver tcpputfiles tcpgetfiles xmltodb dminingoracle deletetable migratetable \
		syncref syncinc
