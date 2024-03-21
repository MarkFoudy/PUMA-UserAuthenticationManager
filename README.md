## PUMA - User Manual

Welcome to PUMA, a user authentication application designed to manage login information and ensure security. This project is the culmination of the knowledge I've acquired this semester.

**Purpose**

PUMA aims to assist system administrators by offering the capability to sort, search, and differentiate authenticated from unauthorized users. This is critical in the constant fight against unlawful access attempts.

To validate my application's functionality, I've prepared four separate text files containing fabricated user information. These files test the robustness of the system, including its ability to detect and handle corrupt data.

**User Data Files**
-   server_dump.txt: This contains 300 individual user records, each having a username, password, IP, and MAC address.
-   server_dump_error.txt: This file includes several invalid IP and MAC addresses that PUMA can identify and disregard.
-   CS5008.txt: A text file with the names of all class members, equipped with random usernames, passwords, IP addresses, and MAC addresses.
-   press.txt: Holds user information for all former US Presidents, each with a unique username, password, IP, and MAC address.

**Key Components**
The zipped PUMA file contains:
-   pumaMenu.c: Menu file.
-   Text files: Simulate imported user information.
-   List.h: Contains function declarations.
-   List.c: Includes linked list ADT and corresponding functions, reading/writing capabilities, bubble sort functionality, binary search component, and a complexity analysis of the searching algorithms.

**Features**

The core features of PUMA include:

1.  **Automatic Password Encryption**: Ensures that even system administrators cannot access unencrypted passwords.
2.  **Searching Algorithms**: Enables efficient and quick searching.
3.  **Error Checking**: Helps recognize valid user data.
4.  **User Separation**: Classifies users into white and blacklists.

**Automatic Password Encryption**

PUMA automatically encrypts each password as it's imported to protect user credentials. A decryption function was created but not included in the interface as there's little reason system administrators should have access to unencrypted user passwords.

**Credential Stuffing Attacks**

Users often reuse passwords across multiple platforms, making them prone to credential stuffing attacks. To protect against this, the option to decrypt individual user passwords has been disabled in the main menu.

**Search and Sort Functionality**

The application includes a search function available in the main menu that can be used to search for users by username, IP address, or MAC address.

**Error Checking and Validation**

I prioritized developing robust error-checking mechanisms to ensure that the system can detect users with inaccurate IP or MAC addresses.

**Triaging users into Whitelists or Blacklists**

Whitelists are trusted users allowed access to the platform, while blacklists are flagged users denied access. This feature, along with effective sorting and searching, forms the crux of the project.

**Populate List Function**

This function serves as the main driver of the program, enabling administrators to import user credential files and process valid data even in the presence of errors.

**Conclusion**

PUMA reflects my commitment to developing an application capable of efficiently processing, parsing, and managing vast amounts of user information. It showcases effective use of search and sort algorithms, error checking, and user data management.

#  Installation

```bash
  git clone https://github.com/MarkFoudy/PUMA-UserAuthenticationManager.git
```

