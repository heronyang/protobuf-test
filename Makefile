.PHONY: clean

C = gcc
CFLAGS = `pkg-config --cflags 'libprotobuf-c >= 1.0.0'`
LFLAGS = `pkg-config --libs 'libprotobuf-c >= 1.0.0'` -lprotobuf-c

all: proto
	$(CC) $(CFLAGS) packet-serialize.c packet.pb-c.c -o packet-serialize $(LFLAGS)
	$(CC) $(CFLAGS) packet-deserialize.c packet.pb-c.c -o packet-deserialize $(LFLAGS)

proto:
	protoc-c --c_out=. packet.proto

clean:
	rm -f packet-serialize packet-deserialize *pb-c*
