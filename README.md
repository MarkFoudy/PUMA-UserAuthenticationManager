## PUMA - User Manual

Welcome to PUMA, a user authentication application designed to manage login information and ensure security. This project is the culmination of the work I did learning C and Assembly Lnaguage through the Northeastern MSCS Course: <br> **CS 5008: Data Structures, Algorithms, and Applications
within Computer Systems** which I took during the Summer 2022.

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

Download the git repository.

```bash
  git clone https://github.com/MarkFoudy/PUMA-UserAuthenticationManager.git
```

Compile the Program: 
```bash
gcc -o pumaMenu pumaMenu.c list.c
```

This command compiles the pumaMenu.c and list.c files, and produces an executable named pumaMenu.

After compiling the program, you can run it with the following command:

```bash
./pumaMenu
```

# Puma Quick Start Guide:
The purpose of this guide is to quickly familiarize end users with PUMA’s functionality.

![image](https://github.com/MarkFoudy/PUMA-UserAuthenticationManager/assets/29990433/4d46f7ee-421d-4059-8ff7-fead00ebff44)


- First Step Importing User Credentials. Menu Option #1
•	To demonstrate PUMA’s functionality, it is necessary to manually import data files.  For this purpose, four separate text files come along with system files to be used to test the functionality of the application.  These files are server_dump.txt, server_dump_error.txt, CS5008.txt and press.txt.

- Second Step Printing User Data. Menu option #2
•	PUMA automatically encrypts each user’s password and only prints the encrypted password protecting the user from malicious actors.
•	PUMA validates each user record being imported contains both valid IP and MAC addresses.
•	Creating whitelists/blacklists for users.  This option allows these lists of users to be printed either to the console or separate text files to be stored.  


- Third Step Searching for individual users. Menu options #3-5
•	PUMA allows system administrators to search for users by username, IP address and MAC address. It utilizes a proprietary binary search algorithm in order to search efficiently and quickly.

- Third step Sorting User files: Menu options #6
•	PUMA utilizes a proprietary developed “bubble sort” algorithm to efficiently sort through large swaths of data.

- Fourth Step deleting imported user list. Menu option #7
•	This final step clears the memory and resets PUMA to import and interact with additional lists of users.


