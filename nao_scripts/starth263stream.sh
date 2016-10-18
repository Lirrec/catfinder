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

gst-launch-0.10 gstrtpbin name=rtpbin latency=0 async-handling=true buffer-mode=none v4l2src always-copy=false queue-size=1 ! video/x-raw-yuv,width=320,height=240,framerate=24/1 ! videoscale ! video/x-raw-yuv,width=176,height=144,framerate=24/1 ! ffenc_h263p flags=0x00000001 ! rtph263ppay ! rtpbin.send_rtp_sink_0 \
 rtpbin.send_rtp_src_0 ! udpsink host=$target_ip port=5000 sync=false \
 rtpbin.send_rtcp_src_0 ! udpsink host=$target_ip port=5001 sync=false async=true \
 udpsrc port=5005 ! rtpbin.recv_rtcp_sink_0

echo "Stream stopped."

QI_LOG_LEVEL=2 ./setmemory.py catfinder_stream ''
