start "" "C:\Program Files\VideoLAN\VLC\VLC.exe" dshow:// :live-caching=100 ":sout=#transcode{vcodec=none,acodec=mp3,ab=128,channels=2,samplerate=44100}:http{mux=mp3,dst=:8080/}" :sout-keep