../nanopb-0.3.9.3-windows-x86/generator-bin/protoc --nanopb_out=. simple_message.proto
mv simple_message.pb.h ../fw_slave/Core/Inc/
mv simple_message.pb.c ../fw_slave/protobuff/