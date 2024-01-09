import socket
import pickle
import sys

BUFFER_SIZE = 1024  # Constant variable for buffer size
JOIN_MESSAGE = 'JOIN'
HELLO_MESSAGE = 'HELLO'
TIME_OUT = 1.5

# Function to connect to the GCD server and retrieve group members
def connect_to_gcd(host, port):
    try:
        with socket.create_connection((host, port)) as gcd_socket:
            gcd_socket.settimeout(TIME_OUT)  # Set socket timeout
            join_message = pickle.dumps(JOIN_MESSAGE)  # Serialize JOIN_MESSAGE
            gcd_socket.sendall(join_message)  # Send JOIN_MESSAGE to the server

            group_members_data = gcd_socket.recv(BUFFER_SIZE)  # Receive group members from the server
            group_members = pickle.loads(group_members_data)  # Deserialize group members

        return group_members
    except (socket.timeout, ConnectionError) as e:
        print(f"Error connecting to GCD: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"Unexpected error connecting to GCD: {e}")
        sys.exit(1)

# Function to send HELLO_MESSAGE to a group member
def send_hello_message(member):
    try:
        member_socket = None
        with socket.create_connection((member['host'], member['port'])) as member_socket:
            hello_message = pickle.dumps(HELLO_MESSAGE)  # Serialize HELLO_MESSAGE
            member_socket.sendall(hello_message)  # Send HELLO_MESSAGE to the member

            response_data = member_socket.recv(BUFFER_SIZE)  # Receive response from the member
            response = pickle.loads(response_data)  # Deserialize the response

            # Print the response from each member
            print(f"Response from {member['host']}:{member['port']}: {response}")
    except (socket.timeout, ConnectionError) as e:
        print(f"Error connecting to {member['host']}:{member['port']}: {e}")
    except Exception as e:
        print(f"Unexpected error connecting to {member['host']}:{member['port']}: {e}")
    finally:
        if member_socket:
            member_socket.close()  # Close the member socket

# Main function
def main():
    try:
        if len(sys.argv) != 3:
            print(f"Usage: python client.py <GCD_HOST_CS1/CS2> <GCD_PORT>")
            sys.exit(1)

        gcd_host, gcd_port = sys.argv[1], int(sys.argv[2])

        group_members = connect_to_gcd(gcd_host, gcd_port)  # Connect to GCD server and get group members

        if not group_members:
            print(f"No group members found.")
            sys.exit(1)

        # Print the response from the GCD server
        print(f"Response from GCD server: {group_members}")

        for member in group_members:
            send_hello_message(member)  # Send hello message to each group member

    except Exception as e:
        print(f"Unexpected error in main: {e}")
        sys.exit(1)

# Entry point of the program
if __name__ == "__main__":
    main()
