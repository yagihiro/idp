# idp

Identity Provider Server Implementation for C++14

# Dependencies

## Mac OX X

```sh
brew install openssl
```

## Linux

todo

# Getting started

## For Mac OS X

### Server Side

First, generate CA private key + public key pair
```
% cd /usr/local/etc/openssl/misc
% ./CA.sh -newca
```

Generated key pairs for CA at the following place:
* CA private key
  * demoCA/private/cakey.pem
* CA public key
  * demoCA/cacert.pem

Next, generate a server key + csr file
```
% openssl genrsa -out server.key 1024
% openssl req -new -key server.key -out server.csr
```

Last, generate a certificate
```
% openssl ca -out server.crt -infiles server.csr
```

Up to this point, everything is ready for ssl server.
* server.key: Specify an argument of set_tls_private_key_path()
* server.crt: Specify an argument of set_tls_certificate_path().

Save the following code in your project:
```
#include <rapid/rapid.h>
#include <signal.h>
#include <iostream>
#include <thread>

static sig_atomic_t _received_sigint = 0;

// Ctrl-C
static void on_sigint(int sig) { _received_sigint = 1; }

int main(int argc, const char* argv[]) {
  if (signal(SIGINT, on_sigint) == SIG_ERR) {
    return EXIT_FAILURE;
  }

  rapid::Server server;
  server.set_port(8080);
  server.use_tls();
  server.set_tls_certificate_path("/usr/local/etc/openssl/misc/serverca.crt");
  server.set_tls_private_key_path("/usr/local/etc/openssl/misc/server.key");
  server.run();

  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(32));
  } while (_received_sigint == 0);

  return EXIT_SUCCESS;
}
```

Build and Run.

### Client Side

Open a terminal and run the following command:
```
% curl https://localhost:8080/index --tlsv1.0 --cacert /usr/local/etc/openssl/misc/demoCA/cacert.pem -k --head
HTTP/1.1 404 Not Found
Content-Length: 0
Content-Type: application/json
```

That is all, you clear the first step.



# Contributing

1. Fork it ( https://github.com/[my-github-username]/idp/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request