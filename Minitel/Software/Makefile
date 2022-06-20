CXX = g++ 
COPT=-I. -x c++

.cpp.o:
	$(CXX) $(COPT) -c $<

.ino.o:
	$(CXX) $(COPT) -c $<


RUNTIME=Minitel.o main.o 

DEMOS=MinitelAsKeyboard \
      MinitelBoobs \
      MinitelDemo \
      MinitelElectroCardio \
      MinitelGoogleSearch \
      MinitelInternetmaTuer \
      MinitelNyanCat \
      MinitelPong \
      MinitelULLA 

all: $(DEMOS)

clean: 
	rm -f $(DEMOS) *.o

MinitelAsKeyboard: examples/MinitelAsKeyboard/MinitelAsKeyboard.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@

MinitelBoobs: examples/MinitelBoobs/MinitelBoobs.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@

MinitelDemo: examples/MinitelDemo/MinitelDemo.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@

MinitelElectroCardio: examples/MinitelElectroCardio/MinitelElectroCardio.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@

MinitelGoogleSearch: examples/MinitelGoogleSearch/MinitelGoogleSearch.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@

MinitelInternetmaTuer: examples/MinitelInternetmaTuer/MinitelInternetmaTuer.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@

MinitelNyanCat: examples/MinitelNyanCat/MinitelNyanCat.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@

MinitelPong: examples/MinitelPong/MinitelPong.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@

MinitelULLA: examples/MinitelULLA/MinitelULLA.ino $(RUNTIME)
	$(CXX) -c $(COPT) $< 
	$(CXX) $@.o $(RUNTIME) -lm -o $@
