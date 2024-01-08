import socket
import pickle
import sys
BUFFER_SIZE = 1024  # Constant variable for buffer size
def connect_to_gcd(host, port):
    try:
        with socket.create_connection((host, port)) as gcd_socket:
            gcd_socket.settimeout(1.5) #R: can we put this as a constant?
            join_message = pickle.dumps('JOIN')
            gcd_socket.sendall(join_message)

            group_members_data = gcd_socket.recv(BUFFER_SIZE)
            group_members = pickle.loads(group_members_data)

        return group_members
    except (socket.timeout, ConnectionError) as e:
        print(f"Error connecting to GCD: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"Unexpected error connecting to GCD: {e}")
        sys.exit(1)

def send_hello_message(member):
    try:
        member_socket = None
        with socket.create_connection((member['host'], member['port'])) as member_socket:
            hello_message = pickle.dumps('HELLO')
            member_socket.sendall(hello_message)

            response_data = member_socket.recv(BUFFER_SIZE)
            response = pickle.loads(response_data)
            # Print the response from each member
            print(f"Response from {member['host']}:{member['port']}: {response}")
    except (socket.timeout, ConnectionError) as e:
        print(f"Error connecting to {member['host']}:{member['port']}: {e}")
    except Exception as e:
        print(f"Unexpected error connecting to {member['host']}:{member['port']}: {e}")
    finally:
        if member_socket:
            member_socket.close()
def main():
    try:
        if len(sys.argv) != 3:
            print("Usage: python client.py <GCD_HOST> <GCD_PORT>") #R: Can we mention cs1 or cs2 here?
            sys.exit(1)

        gcd_host, gcd_port = sys.argv[1], int(sys.argv[2])

        group_members = connect_to_gcd(gcd_host, gcd_port)

        if not group_members:
            print("No group members found.")
            sys.exit(1)

        # Print the response from the GCD server
        print(f"Response from GCD server: {group_members}") 

        for member in group_members:
            send_hello_message(member)

    except Exception as e:
        print(f"Unexpected error in main: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
