#!/bin/bash
target_ip=172.19.255.57
gst-launch-0.10 gstrtpbin name=rtpbin v4l2src ! video/x-raw-yuv,width=320,height=240,framerate=30/1 ! x264enc speed-preset=ultrafast profile=baseline threads=2 bitrate=1024 tune=zerolatency ! rtph264pay ! rtpbin.send_rtp_sink_0 rtpbin.send_rtp_src_0 ! udpsink host=$target_ip port=5000 rtpbin.send_rtcp_src_0 ! udpsink host=$target_ip port=5001 sync=false async=false udpsrc port=5005 ! rtpbin.recv_rtcp_sink_0  alsasrc  ! audio/x-raw-int,rate=16000 ! ffenc_aac ! rtpmp4apay ! rtpbin.send_rtp_sink_1 rtpbin.send_rtp_src_1 ! udpsink host=$target_ip port=5002 rtpbin.send_rtcp_src_1 ! udpsink host=$target_ip port=5003 sync=false async=false udpsrc port=5007 ! rtpbin.recv_rtcp_sink_1