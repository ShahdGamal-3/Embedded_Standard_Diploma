/*
 * Name        : C_project
 * Author      : Shahd Gamal
 * Date        : 8/8/2024
 * Description : Student Management System
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Macro to print a dashed line for consistent output formatting
#define DASHLINE printf("--------------------------------------------------\n")
#define SPACE_DASHLINE printf("           ------------------------\n")

// Enumeration for user choices in the menu
enum choose_function
{
	ADD_STUDENT=1,
	DISPLAY_STUDENTS,
	SEARCH_STUDENT_BY_ID,
	UPDATE_STUDENT,
	DELETE_STUDENT,
	CALCULATE_AVERAGE_GPA,
	SEARCH_HIGHEST_GPA,
	EXIT
};

// Define a structure to store student information
struct student
{
	int id;
	char name[50];
	int age;
	float gpa;
};

// Define a node structure for the linked list
struct node
{
	struct student data;
	struct node *next;
};

// Global pointer to the head of the linked list
struct node *head = NULL;

/**
 * @brief Adds a new student to the linked list.
 * @param ptr Pointer to the student data to be added.
 */
void addStudent (const struct student *const ptr)
{
	struct node *head_copy = head;
	struct node *new_node = (struct node*) malloc (sizeof(struct node));
	if (new_node == NULL)
	{
		printf ("Memory allocation fails!\n");
		return;
	}
	new_node->data = *ptr;
	new_node->next = NULL;

	// If the list is empty, add the new node as the head
	if (head == NULL)
	{
		head = new_node;
		DASHLINE;
		return;
	}

	// Traverse the list to check if the ID already exists and find the last node
	while (head_copy != NULL)
	{
		if (head_copy->data.id == ptr->id)
		{
			DASHLINE;
			printf("This ID is already reserved\n");
			DASHLINE;
			free(new_node);
			return;
		}

		// Move to the next node unless it's the last node
		if (head_copy->next == NULL)
			break;

		head_copy = head_copy->next;
	}

	// Append the new node to the end of the list
	head_copy->next = new_node;
	DASHLINE;
}

/**
 * @brief Displays all students' information in the linked list.
 */
void displayStudents (void)
{
	struct node *head_copy = head;
	if (head == NULL)
	{
		printf ("No students are present\n");
		DASHLINE;
		return;
	}
		// Traverse and display each student's data
	while (head_copy != NULL)
	{
		printf ("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n",
				head_copy->data.id,
				head_copy->data.name,
				head_copy->data.age,
				head_copy->data.gpa);
		head_copy = head_copy->next;
	}
	DASHLINE;
}

/**
 * @brief Searches for a student by their ID.
 * @param id The ID of the student to search for.
 */
void searchStudentByID (int id)
{
	struct node *head_copy = head;

	// Traverse the list to find the student by ID
	while (head_copy != NULL)
	{
		if (head_copy->data.id == id)
		{
			DASHLINE;
			printf ("Student found:\n");
			printf ("ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
					head_copy->data.id, head_copy->data.name,
					head_copy->data.age, head_copy->data.gpa);
			DASHLINE;
			return;
		}
		head_copy = head_copy->next;
	}

	// Student not found
	printf ("Student with ID %d is not found\n", id);
	DASHLINE;
}

/**
 * @brief Updates the information of an existing student by their ID.
 * @param id The ID of the student to update.
 */
void updateStudent (int id)
{
	struct node *head_copy = head;

	// Traverse the list to find the student by ID
	while (head_copy != NULL)
	{
		if (head_copy->data.id == id)
		{
			DASHLINE;
			printf ("Enter new details for the student of ID %d:\n", id);

			// Get updated information from the user
			printf ("Enter new name: ");
			while (getchar() != '\n');
			gets (head_copy->data.name);
			printf ("Enter new age: ");
			scanf ("%d", &head_copy->data.age);
			printf ("Enter new GPA: ");
			scanf ("%f", &head_copy->data.gpa);
			printf ("Student details updated successfully\n");
			DASHLINE;
			return;
		}
		head_copy = head_copy->next;
	}

	// Student not found
	printf ("Student with ID %d is not found\n", id);
	DASHLINE;
}

/**
 * @brief Deletes a student from the linked list by their ID.
 * @param id The ID of the student to delete.
 */
void deleteStudent (int id)
{
	struct node *previous = head;
	struct node *current = head->next;
	struct node *deleted_node = head;

	// Check if the student to delete is the head
	if (head->data.id == id)
	{
		deleted_node = head;
		head = head->next;
		printf ("Student with ID %d is deleted successfully\n", id);
		DASHLINE;
		free (deleted_node);
		return;
	}

	// Traverse the list to find and delete the student by ID
	while (current != NULL)
	{
		if (current->data.id == id)
		{
			deleted_node = current;
			previous->next = current->next;
			printf ("Student with ID %d is deleted successfully\n", id);
			DASHLINE;
			free (deleted_node);
			return;
		}
		current = current->next;
		previous = previous->next;
	}

	// Student not found
	printf ("Student with ID %d is not found\n", id);
	DASHLINE;
}

/**
 * @brief Calculates and returns the average GPA of all students.
 * @return The average GPA.
 */
float calculateAverageGPA (void)
{
	float sumGPA = 0.0;
	int size = 0;
	struct node *head_copy = head;

	// Traverse the list to calculate the sum of GPAs and count of students
	while (head_copy != NULL)
	{
		sumGPA += head_copy->data.gpa;
		size++;
		head_copy = head_copy->next;
	}
	return (size == 0) ? 0.0 : sumGPA / size;
}

/**
 * @brief Searches for and displays the student with the highest GPA.
 */
void searchHighestGPA (void)
{
	struct node *head_copy = head;
	struct node *HighestGPA_student = head;
	float HighestGPA = head_copy->data.gpa;

	// Traverse the list to find the student with the highest GPA
	while (head_copy != NULL)
	{
		if (head_copy->data.gpa > HighestGPA)
		{
			HighestGPA = head_copy->data.gpa;
			HighestGPA_student = head_copy;
		}
		head_copy = head_copy->next;
	}

	// Display the student with the highest GPA
	printf ("Student with the highest GPA:\n");
	printf ("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n",
			HighestGPA_student->data.id,
			HighestGPA_student->data.name,
			HighestGPA_student->data.age,
			HighestGPA_student->data.gpa);
	DASHLINE;
}

/**
 * @brief Frees all nodes in the linked list to avoid memory leaks.
 */
void freeList(void)
{
	struct node *current = head;
	struct node *next;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	head = NULL; // Reset the head to NULL after freeing the list
}

/**
 * @brief Exits the program.
 */
void Exit(void)
{
	freeList(); // Free all nodes in the linked list
	printf("                      Exit\n");
	exit(0);
}

/**
 * @brief Main function to display a menu and process user inputs.
 * @return Always returns 0.
 */
int main (void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	enum choose_function choice;

	while (1)
	{
		printf ("1. Add Student\n2. Display Students\n"
				"3. Search Student by ID\n"
				"4. Update Student Information\n"
				"5. Delete Student\n"
				"6. Calculate Average GPA\n"
				"7. Search for Student with Highest GPA\n"
				"8. Exit\nEnter Choice: ");
		scanf ("%d", (int*)&choice);
		DASHLINE;

		// Process the user's choice
		switch (choice)
		{
		case ADD_STUDENT:
		{
			printf("                 ADD_STUDENT\n");
			SPACE_DASHLINE;
			struct student *new_student = (struct student*) malloc (sizeof(struct student));
			assert (new_student != NULL);
			printf ("Enter student ID: ");
			scanf ("%d", &new_student->id);
			while (getchar() != '\n');
			printf ("Enter name: ");
			gets (new_student->name);
			printf ("Enter age: ");
			scanf ("%d", &new_student->age);
			printf ("Enter GPA: ");
			scanf ("%f", &new_student->gpa);
			addStudent(new_student);
			free (new_student);
		}
			break;

		case DISPLAY_STUDENTS:
			printf("               DISPLAY_STUDENTS\n");
			SPACE_DASHLINE;

			displayStudents();
			break;

		case SEARCH_STUDENT_BY_ID:
		{
			int id_for_search;
			printf("             SEARCH_STUDENT_BY_ID\n");
			SPACE_DASHLINE;
			if (head == NULL)
				{
				    printf ("No students are present\n");
					DASHLINE;
					break;
				}
			printf ("Enter ID to search for a Student: ");
			scanf ("%d", &id_for_search);
			searchStudentByID(id_for_search);
		}
			break;

		case UPDATE_STUDENT:
		{
			int id_for_update;
			printf("                UPDATE_STUDENT\n");
			SPACE_DASHLINE;
			if (head == NULL)
				{
					printf ("No students are present\n");
					DASHLINE;
					break;
				}
			printf ("Enter Student ID to update its information: ");
			scanf ("%d", &id_for_update);
			updateStudent(id_for_update);
		}
			break;

		case DELETE_STUDENT:
		{
			int id_for_delete;
			printf("                DELETE_STUDENT\n");
			SPACE_DASHLINE;
			if (head == NULL)
				{
					printf ("No students are present\n");
					DASHLINE;
					break;
				}
			printf ("Enter Student ID to delete its data: ");
			scanf ("%d", &id_for_delete);
			deleteStudent(id_for_delete);
		}
			break;

		case CALCULATE_AVERAGE_GPA:
			printf("            CALCULATE_AVERAGE_GPA\n");
			SPACE_DASHLINE;
			printf ("Average GPA = %f\n", calculateAverageGPA());
			DASHLINE;
			break;

		case SEARCH_HIGHEST_GPA:
			printf("              SEARCH_HIGHEST_GPA\n");
			SPACE_DASHLINE;
			if (head == NULL)
				{
					printf ("No students are present\n");
					DASHLINE;
					break;
				}
			searchHighestGPA();
			break;

		case EXIT:
			Exit();
			break;

		default:
			printf ("Not allowed choice !!\n");
			DASHLINE;
		}
	}
	return 0;
}
