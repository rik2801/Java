import pickle
import socketserver
import sys

BUF_SZ = 1024  # TCP receive buffer size

class GroupMember(socketserver.BaseRequestHandler):
    """
    A Group Member that acts as a server and responds to peers' messages

    For Theory Lab 1, we respond only to HELLO messages.
    """

    def handle(self):
        """
        Handles the incoming messages - expects only 'HELLO' messages
        """
        raw = self.request.recv(BUF_SZ)  # self.request is the TCP socket connected to the client

        # Input Validation
        if not self.is_valid_message(raw):
            response = bytes('Invalid message format\n', 'utf-8')
        else:
            try:
                message = pickle.loads(raw)
            except (pickle.UnpicklingError, KeyError):
                response = bytes(f'Expected a pickled message, got {raw[:100]}\n', 'utf-8')
            else:
                if message != 'HELLO':
                    response = pickle.dumps(f'Unexpected message: {message}')
                else:
                    message = ('OK', f"Happy to meet you, {self.client_address}")
                    response = pickle.dumps(message)
            finally:
                self.request.sendall(response)

    def is_valid_message(self, raw_message):
        # Implement your validation logic here
        # Return True if the message is valid, otherwise False
        # Example: Check if the message follows a specific format or structure
        try:
            message = pickle.loads(raw_message)
            # Add more validation checks if necessary
            return isinstance(message, str)  # Example: Ensure the message is a string
        except (pickle.UnpicklingError, TypeError):
            return False

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python member.py PORT")
        exit(1)
    port = int(sys.argv[1])
    with socketserver.TCPServer(('', port), GroupMember) as server:
        server.serve_forever()
