#include <iostream>

#include <vector>

#include <string>

using namespace std;

// Structure to store the file name and type struct File {

string name;
string type;
}
;

// Structure to store the user name and files struct User {

string name;
vector<File> files;
}
;

// Function to create a file in the user's sub-directory

void createFile(vector<User> &dir, string user, string file, string type)

{

    // Find the index of the user in the directory int user_index = -1;

    for (int i = 0; i < dir.size(); i++)

    {

        if (dir[i].name == user)

        {

            user_index = i;

            break;
        }
    }

    // If the user is not found, display an error message if (user_index == -1)

    {

        cout << "User not found.\n";
        return;
    }

    // Check if the file name already exists in the user's sub-directory for (File f : dir[user_index].files)

    {

        if (f.name == file)

        {

            cout << "File name already exists.\n";
            return;
        }
    }

    // Add the file name and type to the user's sub-directory

    File new_file;

    new_file.name = file;

    new_file.type = type;

    dir[user_index].files.push_back(new_file);

    cout << "File created successfully.\n";
}

// Function to delete a file from the user's sub-directory void deleteFile(vector<User>& dir, string user, string file)

{

    // Find the index of the user in the directory

    int user_index = -1;

    for (int i = 0; i < dir.size(); i++)

    {

        if (dir[i].name == user)

        {

            user_index = i;

            break;
        }
    }

    // If the user is not found, display an error message if (user_index == -1)

    {

        cout << "User not found.\n";
        return;
    }

    // Find the index of the file name in the user's sub-directory int file_index = -1;

    for (int i = 0; i < dir[user_index].files.size(); i++)

    {

        if (dir[user_index].files[i].name == file)

        {

            file_index = i;
            break;
        }
    }

    // If the file name is not found, display an error message

    if (file_index == -1)

    {

        cout << "File not found.\n";

        return;
    }

    // Remove the file name and type from the user's sub-directory dir[user_index].files.erase(dir[user_index].files.begin() + file_index); cout << "File deleted successfully.\n";
}

// Function to display the contents of the directory void displayDirectory(vector<User>& dir)

{

    // Check if the directory is empty

    if (dir.empty())

    {

        cout << "Directory is empty.\n";

        return;
    }

    // Display the user names and files in the directory cout << "Directory contains:\n";

    for (User u : dir)

    {

        cout << u.name << ":\n";
        for (File f : u.files)

        {

            cout << f.name << "." << f.type << "\n";
        }
    }
}