#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int validate_name(char *user_name)
{

	for(int i = 0; user_name[i] != '\0'; i++)
	{
	
	if(!((user_name[i] >=  'A') && ( user_name[i] <= 'Z') || (user_name[i] >=  'a') && ( user_name[i] <='z') || (user_name[i] == ' ')))
	{
		
		return 1;
	}

	}
	return 0;
}
int validate_number(char *number)
{
if(strlen(number) > 10 || strlen(number) < 10 )
{
	return 1;
}
        for(int i = 0; number[i] != '\0'; i++)
        {
              
        if(!(( number[i] >= '0' ) && ( number[i] <= '9')))
        {

                return 1;
        }
       
        }
	return 0;
}
int validate_mail(char *user_mail)
{
       	int flag = 1;

        if(((user_mail[0]>=  'A') && (user_mail[0] <= 'Z')) || ((user_mail[0] >=  'a') && (user_mail[0] <='z')))
        {
		char email[20] = "@email.com";
		char gmail[20] = "@gmail.com";
		int j = strlen(gmail) - 1;
		
                int size = strlen(user_mail);
        for(int i = size-1; i  >= (size-10);i--)
	{

	if(user_mail[i] == email[j] || user_mail[i] == gmail[j])
        {
                       flag = 0;
                
        }
        else
        {
                return 1;

        }
j--;
        }
		return flag;
	}
	else
	{
		return 1;
	}
}


int listContacts(AddressBook *addressBook, int sortCriteria) 
{
            
    // Sort contacts based on the chosen criteria
    for(int i = 0; i < addressBook -> contactCount-1; i++)
    {
	    for(int j = 0; j < (addressBook -> contactCount -i -1); j++)
	    {

	    switch(sortCriteria)
	    {
		    //sort creteria by name
		            case 1:
			    {
				    if((strcmp(addressBook -> contacts[j].name,addressBook -> contacts[j+1].name) > 0))
				    {
					    Contact temp = addressBook -> contacts[j];
					    addressBook -> contacts[j] = addressBook -> contacts[j+1];
					    addressBook -> contacts[j+1] = temp;
					    
				    }
				    break;
			    }
			    //sort creteria by phone number
			    case 2:
                            {
                                    if((strcmp(addressBook -> contacts[j].phone,addressBook -> contacts[j+1].phone) > 0))
                                    {
                                            Contact temp = addressBook -> contacts[j];
                                            addressBook -> contacts[j] = addressBook -> contacts[j+1];
                                            addressBook -> contacts[j+1] = temp;
					   
                                    }
                                    break;
                            }
			    case 3:
                            {
                                    if((strcmp(addressBook -> contacts[j].email,addressBook -> contacts[j+1].email) > 0))
                                    {
                                            Contact temp = addressBook -> contacts[j];
                                            addressBook -> contacts[j] = addressBook -> contacts[j+1];
                                            addressBook -> contacts[j+1] = temp;
					     
                                    }
                                    break;
                            }
			    default:
			    {
				    printf("Invalid choice\n");
				    return -1;
				    break;
			    }



	    }
	    }
    }
                   
                   
                   //Display the name
		   printf("\nSorted Contact List:\n");
                   for(int i = 0; i < addressBook -> contactCount; i++)
                    {
                        printf("\nCONTACT NUMBER %d\n",i+1);
                        printf("Name: %s\n",addressBook -> contacts[i].name);
                        printf("Phone Number: %s\n",addressBook -> contacts[i].phone);
                        printf("Mail ID: %s\n",addressBook -> contacts[i].email);
			

                    }
                    printf("\nTotal Contact is %d\n", addressBook -> contactCount);
		    return 0;
		   
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
 /* Define the logic to create a Contacts */
	char user_name[50], user_mobile[20], user_mail[50];
	int valid;
  do
     {
    //STEP1: Read the name from user
    printf("\nEnter The Name: ");
    scanf(" %49[^\n]",user_name);

    //Step2: validate the name
     valid = validate_name(user_name);

    //STEP3: if valid -> goto STEP4

    //else-> print the error msg
    if(valid == 1)
    {
     printf("You Entered invalid Name: \n");
    }

    }while(valid == 1);

do
    {	
    //STEP4: Read the mobile_no from usr
    printf("Enter The Phone Number(91): ");
    scanf("%s",user_mobile);

    //STEP5: Validate the mobile number
    valid = validate_number(user_mobile);

    //STEP6: if valid -> goto STEP7
    
    // else->print the error, Goto STEP4
    if(valid == 1)
    {
	    printf("You Entered invalid Phone Number\n");
    }
    }while(valid == 1);

do
    {
    //STEP7: Read the email_id from user
    printf("Enter The Mail Id: ");
    scanf("%s",user_mail);

    //STEP8: Validate the Mail Id
    valid = validate_mail(user_mail);
    //STEP9: if valid -> goto STEP10
     
    //else-> print the error, Goto STEP7
    if(valid == 1)
    {
	    printf("You Entered invalid Mail Id: \n");
    }
    }while(valid == 1);
    //STEP10: Save the contact in structure and display the message
    strcpy(addressBook -> contacts[addressBook -> contactCount].name,user_name /*Destination, Source*/);
    strcpy(addressBook -> contacts[addressBook -> contactCount].phone,user_mobile);
    strcpy(addressBook -> contacts[addressBook -> contactCount].email,user_mail);
    addressBook -> contactCount++;
    printf("INFO: Contact added Successfully...:)\n");
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
	//STEP1: select from the menu(Based on What you want to search, 1. name, 2.Mobile_no, 3.Mail_ID)
	printf("\nBased on What you want to Search\n1.Name\n2.Mobile Number\n3.Mail_ID\nEnter The choice: ");
	char user_name[50], user_mobile[20], user_mail[50];
	int choice, valid, count = -1, found = 0;
	scanf("%d",&choice);
	//STEP2: Based on input read the credential
	switch(choice)
	{
		case 1:
			{	       
                       do
                        {
                          //STEP1: Read the name from user
                          printf("Enter The Name: ");
                          scanf(" %49[^\n]",user_name);

                          //Step2: validate the name
                          valid = validate_name(user_name);

                         //STEP3: if valid -> goto STEP4

                         //else-> print the error msg
                         if(valid == 1)
                         {
                            printf("You Entered invalid Name: \n");
                         }

                       }while(valid == 1);
		       // STEP4: Search the name in structure 
               for(int i = 0; i < addressBook -> contactCount; i++)
		{ 
	           char *cptr = strstr(user_name,addressBook -> contacts[i].name) ;
		if(cptr != NULL)
	          {
		    count = i;
		    found = 1;
		    break;
	          }
		}

		    
		     break;
			}
		case 2:
			{
			
			 do
                            {
                               //STEP4: Read the mobile_no from usr
                                printf("Enter The Phone Number(91): ");
                                scanf("%s",user_mobile);

                                //STEP5: Validate the mobile number
                                valid = validate_number(user_mobile);

                               //STEP6: if valid -> goto STEP7

                              // else->print the error, Goto STEP4
                              if(valid == 1)
                              {
                                printf("You Entered invalid Phone Number\n");
                              }
                             }while(valid == 1);
			     // STEP4: Search the name in structure
                        for(int i = 0; i < addressBook -> contactCount; i++)
                           {
                              char *cptr = strstr(user_mobile,addressBook -> contacts[i].phone) ;
                              if(cptr != NULL)
                              {
                                      count = i;
                                      found = 1;
                                      break;
                              }
                           }
                       break;
		        }
	        case 3:
		{
				//Read the Mail_Id and validate it

                            do
                               {
                                //STEP7: Read the email_id from user
                                 printf("Enter The Mail Id: ");
                                 scanf("%s",user_mail);

                                //STEP8: Validate the Mail Id
                                 valid = validate_mail(user_mail);
                                //STEP9: if valid -> goto STEP10

                                //else-> print the error, Goto STEP7
                           if(valid == 1)
                            {
                              printf("You Entered invalid Mail Id: \n");
                            }
                           }while(valid == 1);

			 // STEP4: Search the name in structure
                        for(int i = 0; i < addressBook -> contactCount; i++)
                           {
                              char *cptr = strstr(user_mail,addressBook -> contacts[i].email) ;
                               if(cptr != NULL)
                              {
                                      count = i;
                                      found = 1;
                                      break;
                              }
                           }
                       break;
	         }
		default:
		{
			printf("Invalid choice. Please try again.\n");
	                found = 1;	
	        }
	}
	 //STEP5: If present -> Display the contact detils, Goto main menu
	if(count >= 0)
	{
		printf("\nContact is Found\n");
                   printf("Name: %s\n",addressBook -> contacts[count].name);
		   printf("Phone Number: %s\n",addressBook -> contacts[count].phone);
		   printf("Mail ID: %s\n",addressBook -> contacts[count].email);
	}
	//If nnot present -> print error message, Then goto main menu (return)
	else if(found == 0)
	{
		printf("Contact is Not Found\n");
	}
	return count;

}

int editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
            char user_name[50], user_mobile[20], user_mail[50];
	//STEP1: Search the contact(call search_contact function)
          int count = searchContact(addressBook);	
	//STEP2: Collect the return Value frome searchcontact(found_index)
	
	//Step3: if found_index >= 0 -> Goto Step4
	// else found_inex == -1 -> Goto main_menu
	if(count < 0)
	{
		return -1;
	}
	
	// STEP4: selesct from the menu(what you want edit, 1.name, 2.Mobile_no, 3.Mail_Id)
	printf("\nWhat You Want To Edit,\n1.Name,\n2.Phone Number,\n3.Mail Id\n");
	int choice, valid;
	//STEP5: Based on input read the credential
	printf("Enter Your Choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			{
				 do
                        {
                          //STEP1: Read the name from user
                          printf("Enter The Name: ");
                          scanf(" %49[^\n]",user_name);

                          //Step2: validate the name
                          valid = validate_name(user_name);

                         //STEP3: if valid -> goto STEP4

                         //else-> print the error msg
                         if(valid == 1)
                         {
                            printf("You Entered invalid Name: \n");
                         }

                       }while(valid == 1);
			
				
				 strcpy(addressBook -> contacts[count].name,user_name);
				 printf("Name is Edited Successfully...:~)\n");

			break;
			}
                case 2:
			{   do
                              {
                                 //STEP4: Read the mobile_no from usr
                                 printf("Enter The Phone Number(91): ");
                                 scanf("%s",user_mobile);

                                //STEP5: Validate the mobile number
                                 valid = validate_number(user_mobile);

                                //STEP6: if valid -> goto STEP7

                                // else->print the error, Goto STEP4
                                 if(valid == 1)
                                     {
                                      printf("You Entered invalid Phone Number\n");
                                      }
                                }while(valid == 1);
                                 strcpy(addressBook -> contacts[count].phone,user_mobile);
                                 printf("Phone number is Edited Successfully...:~)\n");

				break;
			}
		case 3:
			{
				do
                                  {
                                   //STEP7: Read the email_id from user
                                    printf("Enter The Mail Id: ");
                                    scanf("%s",user_mail);

                                  //STEP8: Validate the Mail Id
                                  valid = validate_mail(user_mail);
                                  //STEP9: if valid -> goto STEP10

                                 //else-> print the error, Goto STEP7
                                 if(valid == 1)
                                  {
                                   printf("You Entered invalid Mail Id: \n");
                                  }
                                 }while(valid == 1);
				strcpy(addressBook -> contacts[count].email,user_mail);
				printf("Mail Id is Edited Successfully...:~)\n");
				break;
			}
		default:
			{
				printf("Invalid choice. Please try again.\n");
				break;
			}
	}
	
	//STEP6: Validate the input
	
	//STEP7: IF valid -> Replace the new credential insted of the old one.
	
	//  if not valid -> Goto Step5
	
    
}

int deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deleteconact */
	char choice;
	//STEP1: Search the contact(call search_contact function)
	 int count = searchContact(addressBook);
        //STEP2: Collect the return Value frome searchcontact(found_index)

        //Step3: if found_index >= 0 -> Goto Step4
        // else found_inex == -1 -> Goto main_menu
        if(count < 0)
        {
                return -1;
        }
	
	//STEP4: Ask the confirmation (Do you want to delete(Y/N)
	printf("Do you Want to delete this Contact from the list(Y/N): ");
	scanf(" %c",&choice);
	//STEP5: If user selected Yes(Y/y) -> Delete the contact from structure and print thr msg.
	if((choice == 'y' || choice == 'Y'))
	{
		for(int i = count; i < addressBook -> contactCount; i++)
		{
			addressBook -> contacts[i] =  addressBook -> contacts[i+1];
		}
		 addressBook -> contactCount--;
		 printf("Contact is Deleted Successfully\n");
	}
	//       else user selected No(N/n) -> Don't delelte, Goto main menu
	else if((choice == 'N' || choice == 'n'))
	{
		printf("Contact is Not deleted\n");
		return -1;
	}
	else
	{
		printf("Invalid Choice\n");
	}

	
	
   
}
