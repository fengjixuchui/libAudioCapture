# libAudioCapture
capture desktop sounds and mic audio (currently, linux only)

### Build library

~~~~
$ git clone https://github.com/CPlusPlusTW/libAudioCapture.git
$ cd libAudioCapture
$ qmake ibAudioCapture.pro
$ make
~~~~

### Build example

The example demonstrate how to record 10 seconds of desktop sounds with libAudioCapture

~~~~
$ cd examples
$ qmake ibAudioCapture-demo.pro
$ make
$ export LD_LIBRARY_PATH=../
$ ./libAudioCapture-demo
~~~~

Play with following command

~~~~
$ play -t raw -r 44100 -e signed -b 16 -c 2 sound.pcm
(or)
$ ffplay -f s16le -ar 44100 -ac 2 sound.pcm 
~~~~

