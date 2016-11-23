.PHONY: clean

C = gcc
CFLAGS = `pkg-config --cflags 'libprotobuf-c >= 1.0.0'`
LDFLAGS = `pkg-config --libs 'libprotobuf-c >= 1.0.0'` -lprotobuf-c

all: proto
	$(CC) $(CFLAGS) packet-serialize.c packet.pb-c.c -o packet-serialize $(LDFLAGS)
	$(CC) $(CFLAGS) packet-deserialize.c packet.pb-c.c -o packet-deserialize $(LDFLAGS)

proto:
	protoc-c --c_out=. packet.proto

clean:
	rm -f packet-serialize packet-deserialize *pb-c*
