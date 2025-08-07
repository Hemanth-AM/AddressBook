#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv", "w");
    if (fptr == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    printf("Saving %d contacts...\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
     {
    

        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf("Contacts saved successfully.\n");
}


void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv", "r");
    if (fptr == NULL) {
        printf("Error: Could not open file for reading.\n");
        return;
    }

    addressBook->contactCount = 0;

    while (fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;

        
    }

    fclose(fptr);
    printf("Loaded %d contacts.\n", addressBook->contactCount);
}
