
PUBCPP = /myproject/public/_public.cpp

PUBH = -I /myproject/public

all:crtsurfdata

crtsurfdata:crtsurfdata.cpp
	g++ -g -o $@ $^ $(PUBCPP) $(PUBH)
	cp -f crtsurfdata ../bin/.

clean:
	rm -f crtsurfdata
