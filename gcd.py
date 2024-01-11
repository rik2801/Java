import pickle
import socketserver
import sys

BUFFER_SIZE = 1024  # TCP receive buffer size

class GroupCoordinatorDaemon(socketserver.BaseRequestHandler):
    """
    A Group Coordinator Daemon (GCD) which will respond with a list of potential group members to a text message JOIN
    with list of group members to contact.

    For Theory Lab 1, we just respond with a fixed list of two servers.
    """
    JOIN_RESPONSE = [
        {'host': 'cs2.seattleu.edu', 'port': 10777},
        {'host': 'cs2.seattleu.edu', 'port': 10766},
        {'host': 'cs2.seattleu.edu', 'port': 10755}
    ]

    def handle(self):
        """
        Handles the incoming messages - expects only 'JOIN' messages
        """
        raw = self.request.recv(BUFFER_SIZE)
        print(self.client_address)

        # Input Validation
        if not self.is_valid_message(raw):
            response = bytes('Invalid message format\n', 'utf-8')
        else:
            try:
                message = pickle.loads(raw)
            except (pickle.UnpicklingError, KeyError):
                response = bytes(f'Expected a pickled message, got {raw[:100]}\n', 'utf-8')
            else:
                if message != 'JOIN':
                    response = pickle.dumps(f'Unexpected message: {message}')
                else:
                    response = pickle.dumps(self.JOIN_RESPONSE)
            finally:
                self.request.sendall(response)

    def is_valid_message(self, raw_message):
        # Implement your validation logic here
        # Return True if the message is valid, otherwise False
        try:
            message = pickle.loads(raw_message)
            # Add more validation checks if necessary
            return isinstance(message, str) and message == 'JOIN'
        except (pickle.UnpicklingError, TypeError):
            return False

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python gcd.py GCDPORT")
        exit(1)
    port = int(sys.argv[1])
    with socketserver.TCPServer(('', port), GroupCoordinatorDaemon) as server:
        server.serve_forever()
