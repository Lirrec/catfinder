#!/bin/bash

cd $(dirname $0)
target_ip=$(QI_LOG_LEVEL=2 ./getmemory.py catfinder_ip)



if [[ -z $target_ip ]]
then
        echo "no ip set in ALMemory key 'catfinder_ip'";
        exit;
fi

echo "Target IP for stream is: $target_ip"

QI_LOG_LEVEL=2 ./setmemory.py catfinder_stream running

gst-launch-0.10 gstrtpbin latency=0  name=rtpbin v4l2src always-copy=false queue-size=2 ! queue ! video/x-raw-yuv,width=320,height=240,framerate=12/1 ! x264enc speed-preset=ultrafast profile=baseline threads=2 bitrate=1024 tune=zerolatency !  queue ! rtph264pay ! rtpbin.send_rtp_sink_0 rtpbin.send_rtp_src_0 ! udpsink host=$target_ip port=5000 rtpbin.send_rtcp_src_0 ! udpsink host=$target_ip port=5001 sync=false async=false udpsrc port=5005 ! rtpbin.recv_rtcp_sink_0  alsasrc ! queue ! audio/x-raw-int,rate=32000 ! ffenc_aac ! rtpmp4apay ! rtpbin.send_rtp_sink_1 rtpbin.send_rtp_src_1 ! udpsink host=$target_ip port=5002 rtpbin.send_rtcp_src_1 ! udpsink host=$target_ip port=5003 sync=false async=false udpsrc port=5007 ! rtpbin.recv_rtcp_sink_1

echo "Stream stopped."

QI_LOG_LEVEL=2 ./setmemory.py catfinder_stream ''