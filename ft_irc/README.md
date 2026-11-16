*This project has been created as part of the 42 curriculum by sheiles.*

# ft_irc

## Description

`ft_irc` is a C++98 Internet Relay Chat (IRC) server. It accepts TCP clients,
authenticates them with a server password, and lets them communicate through
channels or private messages. The server uses non-blocking sockets and one
`poll()` loop to handle all connections.

Implemented features include nickname and user registration, channel creation
and membership, channel and private messaging, and the operator commands
`KICK`, `INVITE`, `TOPIC`, and `MODE` (`i`, `t`, `k`, `o`, and `l`).
Graceful disconnects flush pending output for up to five seconds; saturated
output queues close immediately.

## Instructions

Build on a POSIX system with a C++98 compiler:

```sh
make
```

Run the server with a port and a connection password:

```sh
./ircserv 6667 secret
```

Connect an IRC client to `127.0.0.1:6667` and use `secret` as its server
password. For a minimal manual test with netcat:

```sh
nc 127.0.0.1 6667
PASS secret
NICK alice
USER alice 0 * :Alice Example
JOIN #general
```

Use `make clean` to remove object files, `make fclean` to remove all build
outputs, or `make re` to rebuild from scratch.

## Resources

- [RFC 1459: Internet Relay Chat Protocol](https://www.rfc-editor.org/rfc/rfc1459)
- [RFC 2812: Internet Relay Chat: Client Protocol](https://www.rfc-editor.org/rfc/rfc2812)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)

AI assistance was used to scaffold the initial server implementation, organize
the IRC command handling, and draft this documentation. The resulting code
and behavior should be reviewed and tested as part of the project evaluation.
