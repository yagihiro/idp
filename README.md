# idp

Identity Provider Server Implementation for C++14

# Dependencies

## Mac OX X

* openssl

```sh
brew install openssl
```

* [rapid](https://github.com/yagihiro/rapid)

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

Next, generate a certificate
```
% openssl ca -out server.crt -infiles server.csr
```

Up to this point, everything is ready for ssl server.
* server.key: Specify an argument of set_tls_private_key_path()
* server.crt: Specify an argument of set_tls_certificate_path().

Next, clone codes from github:
```
% git clone https://github.com/yagihiro/idp.git
% cd idp
% git submodule update --init
```

Final, Build and Run.

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
