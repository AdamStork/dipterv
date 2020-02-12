../nanopb-0.3.9.3-windows-x86/generator-bin/protoc --nanopb_out=. functional_test.proto
../nanopb-0.3.9.3-windows-x86/generator-bin/protoc -I=. --python_out=. functional_test.proto
mv functional_test.pb.h ../func_test/Core/Inc/
mv functional_test.pb.c ../func_test/protobuff/
mv functional_test_pb2.py ../pyQt/