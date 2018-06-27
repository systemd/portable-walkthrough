/* SPDX-License-Identifier: LGPL-2.1+ */

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Let's define assert_se() as guaranteed side effect version of assert(): even if NDEBUG is set the commands specified
 * are executed. */
#ifdef NDEBUG
#define assert_se(x) (void) (x)
#else
#define assert_se(x) assert(x)
#endif

int main(int argc, char *argv[]) {
        sigset_t ss;
        int sig;

        fprintf(stderr, "Initializing.\n");

        assert_se(sigemptyset(&ss) >= 0);
        assert_se(sigaddset(&ss, SIGTERM) >= 0);
        assert_se(sigaddset(&ss, SIGINT) >= 0);
        assert_se(sigprocmask(SIG_BLOCK, &ss, NULL) >= 0);

        if (sigwait(&ss, &sig) < 0) {
                fprintf(stderr, "Failed to sigwait(): %m\n");
                goto fail;
        }

        if (sig == SIGTERM)
                fprintf(stderr, "Got SIGTERM.\n");
        else {
                assert(sig == SIGINT);
                fprintf(stderr, "Got SIGINT.\n");
        }

        fprintf(stderr, "Exiting cleanly.\n");
        return EXIT_SUCCESS;

fail:
        fprintf(stderr, "Exiting with failure.\n");
        return EXIT_FAILURE;
}
