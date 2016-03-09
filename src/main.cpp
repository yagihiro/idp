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

  server.get("/", [](const rapid::Request& req) -> rapid::ResponsePtr {
    rapid::Response response;

    response.set_status_code(200);
    response.set_headers({{"Content-Type", "application/json"}});
    response.set_body("{'key':'value'}");

    return std::make_shared<rapid::Response>(response);
  });

  server.run();

  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(32));
  } while (_received_sigint == 0);

  return EXIT_SUCCESS;
}
