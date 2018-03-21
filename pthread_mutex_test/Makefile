XX     = gcc 
CFLAGS = -g
CLIBS  = -lpthread
TARGET = pthread_mutex_test

#template change variable
OBJECTS =  $(patsubst %.c,%.o,$(wildcard ./*.c))
INCLUDES = $(wildcard ./*.h)

	
#$^ all required
# $(TARGET) : $(OBJECTS)
# 	$(XX) $(CFLAGS) $^ -o $@ $(CLIBS)

# $(OBJECTS) :%.o : %.c
# 	$(XX) -c $(CFLAGS) $< -o $@ $(INCLUDE_DIRS)

# $@ : first object 
# $< : first required
all:
	echo $(OBJECTS)
	echo $(INCLUDES)
	
.PHONY : clean
clean:
	rm -rf $(TARGET) $(OBJECTS)