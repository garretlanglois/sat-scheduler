##Example implemenation with python generated by Claude for testing

import ctypes
import json
import os

# Hardcoded path to the DLL
DLL_PATH = r"C:\Users\gasla\Documents\sat-scheduler\json_parser_source\src\build\bin\Debug\commmand_parser.dll"

# Load the shared library
command_lib = ctypes.CDLL(DLL_PATH)

# Define the command_t structure for ctypes
class CommandT(ctypes.Structure):
    _fields_ = [
        ("commandId", ctypes.c_char_p),
        ("issuedBy", ctypes.c_char_p),
        ("issuedAt", ctypes.c_char_p),
        ("priority", ctypes.c_char_p),
        ("jwt", ctypes.c_char_p),
        ("operation", ctypes.c_char_p),
        ("deltaV", ctypes.c_double),
        ("axis", ctypes.c_char_p)
    ]

# Define the function prototypes
command_lib.parse_command.argtypes = [ctypes.c_char_p, ctypes.POINTER(ctypes.POINTER(CommandT))]
command_lib.parse_command.restype = ctypes.c_int

command_lib.free_memory.argtypes = [ctypes.POINTER(CommandT)]
command_lib.free_memory.restype = None

def parse_command_json(json_file_path):
    """
    Parse a command JSON file using the C++ library and return the command data.
    """
    # Read the JSON file
    with open(json_file_path, 'r') as f:
        json_str = f.read()
    
    # Create a pointer to hold the result
    cmd_ptr = ctypes.POINTER(CommandT)()
    
    # Call the C++ function
    result = command_lib.parse_command(json_str.encode('utf-8'), ctypes.byref(cmd_ptr))
    
    if result != 0:
        print(f"Error parsing command: Error code {result}")
        return None
    
    # Extract data from the C structure
    command_data = {
        "commandId": cmd_ptr.contents.commandId.decode('utf-8') if cmd_ptr.contents.commandId else None,
        "issuedBy": cmd_ptr.contents.issuedBy.decode('utf-8') if cmd_ptr.contents.issuedBy else None,
        "issuedAt": cmd_ptr.contents.issuedAt.decode('utf-8') if cmd_ptr.contents.issuedAt else None,
        "priority": cmd_ptr.contents.priority.decode('utf-8') if cmd_ptr.contents.priority else None,
        "jwt": cmd_ptr.contents.jwt.decode('utf-8') if cmd_ptr.contents.jwt else None,
        "operation": cmd_ptr.contents.operation.decode('utf-8') if cmd_ptr.contents.operation else None,
        "deltaV": cmd_ptr.contents.deltaV,
        "axis": cmd_ptr.contents.axis.decode('utf-8') if cmd_ptr.contents.axis else None
    }
    
    # Free the memory allocated by the C++ library
    command_lib.free_memory(cmd_ptr)
    
    return command_data

def main():
    # Hardcoded path to the JSON file
    json_file_path = r"command_t.json"
    
    # Parse the command
    command = parse_command_json(json_file_path)
    
    if command:
        print("Command parsed successfully:")
        print(json.dumps(command, indent=2))
        
        # Example of using the parsed data
        print(f"\nProcessing command {command['commandId']}:")
        print(f"Operation: {command['operation']}")
        
        if command['operation'] == 'adjustOrbit' and command['deltaV'] is not None and command['axis']:
            print(f"Adjusting orbit with deltaV = {command['deltaV']} on {command['axis']} axis")

if __name__ == "__main__":
    main()
