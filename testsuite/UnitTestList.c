/*
 * UnitTestList.c
 * Original Author: Marissa
 * Modified By: Stephen
 */

// Includes
#include <stdio.h>
#include <stdlib.h>

#include "../libsrc/common.h"
#include "Object.h"
#include "../libsrc/Node.h"
#include "../libsrc/List.h"

// Preprocessor definitions
#define STR(x) #x

/*
 * macro to mimic the functionality of assert() from <assert.h>. The difference is that this version doesn't exit the program entirely.
 * It will just break out of the current function (or test case in this context).
 */
#define myassert(expr) if(!(expr)){ fprintf(stderr, "\t[assertion failed] %s: %s\n", __PRETTY_FUNCTION__, STR(expr)); return FALSE; }

// Instance data
ListPtr testlist;
int testCount = 0;
int passCount = 0;

// Print out methods
void printTestInfo(char* testName, char *info) {
	fprintf(stdout, "%s - %s\n", testName, info);
}

void printTestResult(char* testName, Boolean passed) {
	if (passed == TRUE) {
		fprintf(stdout, "%s - %s\n\n", "[PASSED]", testName);
	}
	else {
		fprintf(stdout, "%s - %s\n\n", "[FAILED]", testName);
	}
}

void beforeTest(char* testName) {
	printTestInfo(testName, "Running...");
//	testlist = createList(compareTo, toString, freeObject);
	testCount++;
}
void afterTest(char* testName, Boolean result) {
	printTestResult(testName, result);
//	freeList(testlist);
	passCount += result;
}

void initialize() {
	freeList(testlist);
	testlist = createList(compareTo, toString, freeObject);
}

NodePtr createTestNode(int jobid) {
	ObjectPtr job = createObject(jobid, "cmd args");
	NodePtr node = createNode(job);
	return node;
}

// Unit tests
Boolean addAtFrontWithNoNodes() {
	NodePtr node = createTestNode(1);

	addAtFront(testlist, node);

	myassert(testlist->size == 1)
	myassert(testlist->head == node)
	myassert(testlist->tail == node)
	myassert(testlist->head->next == NULL)
	myassert(testlist->head->prev == NULL)

	return TRUE;
}

Boolean addAtFrontWithOneNode() {
	NodePtr node = createTestNode(2);

	addAtFront(testlist, node);

	myassert(testlist->size == 2)
	myassert(testlist->head == node)
	myassert(testlist->tail == testlist->head->next)
	myassert(testlist->head->next == testlist->tail)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->prev == testlist->head)
	myassert(testlist->tail->next == NULL)

	return TRUE;
}

Boolean addAtRearWithNoNodes() {
	initialize();
	NodePtr node = createTestNode(1);
	addAtRear(testlist, node);

	myassert(testlist->size == 1)
	myassert(testlist->head == node)
	myassert(testlist->tail == node)
	myassert(testlist->head->next == NULL)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->prev == NULL)
	myassert(testlist->tail->next == NULL)

	return TRUE;
}

Boolean addAtRearWithOneNode() {
	NodePtr node = createTestNode(2);

	addAtRear(testlist, node);

	myassert(testlist->size == 2)
	myassert(testlist->head == testlist->tail->prev)
	myassert(testlist->tail == node)
	myassert(testlist->head->next == testlist->tail)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->prev == testlist->head)
	myassert(testlist->tail->next == NULL)

	return TRUE;
}

Boolean removeFromFrontWithNoNode() {
	initialize();

	NodePtr returnNode = removeFront(testlist);

	myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(returnNode == NULL)

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean removeFromFrontWithOneNode() {
	initialize();
	NodePtr node = createTestNode(1);
	addAtFront(testlist, node);

	NodePtr returnNode = removeFront(testlist);

	myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(returnNode == node)

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean removeFromFrontWithManyNodes() {
	initialize();
	NodePtr node1 = createTestNode(1);
	NodePtr node2 = createTestNode(2);
	NodePtr node3 = createTestNode(3);
	NodePtr node4 = createTestNode(4);

	addAtFront(testlist, node1);
	addAtFront(testlist, node2);
	addAtFront(testlist, node3);
	addAtFront(testlist, node4);

	NodePtr returnNode = removeFront(testlist);

	myassert(testlist->size == 3)
	myassert(testlist->head == node3)
	myassert(testlist->tail == node1)
	myassert(returnNode == node4)

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean removeFromRearWithNoNode() {
	initialize();

	NodePtr returnNode = removeRear(testlist);

	myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(returnNode == NULL)

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean removeFromRearWithOneNode() {
	initialize();
	NodePtr node = createTestNode(1);
	addAtFront(testlist, node);

	NodePtr returnNode = removeRear(testlist);

	myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(returnNode == node)

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean removeFromRearWithManyNodes() {
	initialize();
	NodePtr node1 = createTestNode(1);
	NodePtr node2 = createTestNode(2);
	NodePtr node3 = createTestNode(3);
	NodePtr node4 = createTestNode(4);

	addAtFront(testlist, node1);
	addAtFront(testlist, node2);
	addAtFront(testlist, node3);
	addAtFront(testlist, node4);

	NodePtr returnNode = removeRear(testlist);

	myassert(testlist->size == 3)
	myassert(testlist->head == node4)
	myassert(testlist->tail == node2)
	myassert(returnNode == node1)

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean removeFromListWithNoNode() {
	initialize();
	NodePtr node = createTestNode(1);
	NodePtr returnNode = removeNode(testlist, node);

	myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(returnNode == NULL)

	freeNode(node, freeObject);
	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean removeFromListWithOneNode() {
	initialize();
	NodePtr node = createTestNode(1);
	addAtFront(testlist, node);

	NodePtr returnNode = removeNode(testlist, node);

	myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(returnNode == node)

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean removeFromListWithManyNodes() {
	initialize();
	NodePtr node1 = createTestNode(1);
	NodePtr node2 = createTestNode(2);
	NodePtr node3 = createTestNode(3);
	NodePtr node4 = createTestNode(4);

	addAtFront(testlist, node1);
	addAtFront(testlist, node2);
	addAtFront(testlist, node3);
	addAtFront(testlist, node4);

	NodePtr returnNode = removeNode(testlist, node2);

	myassert(testlist->size == 3)
	myassert(testlist->head == node4)
	myassert(testlist->tail == node1)
	myassert(returnNode == node2)

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean addNullNodeToFront() {
	initialize();
	NodePtr node = NULL;
	addAtFront(testlist, node);

	myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)

	return TRUE;
}

Boolean addNullNodeToRear() {
	initialize();
	NodePtr node = NULL;
	addAtRear(testlist, node);

	myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)

	return TRUE;
}

Boolean testIsEmpty() {
	initialize();
	NodePtr node = createTestNode(1);

	Boolean empty = isEmpty(testlist);
	myassert(empty == TRUE);

	addAtFront(testlist, node);
	Boolean notEmpty = isEmpty(testlist);
	myassert(notEmpty == FALSE);

	NodePtr returnNode = removeNode(testlist, node);
	empty = isEmpty(testlist);
	myassert(empty == TRUE);

	freeNode(returnNode, freeObject);
	return TRUE;
}

Boolean testReverse() {
	initialize();
	int numNodes = 10;
	ListPtr list1 = createList(compareTo, toString, freeObject);
	ListPtr list2 = createList(compareTo, toString, freeObject);
	NodePtr node, test1, test2;

	int i;
	for (i = 0; i < numNodes; i++) {
		node = createTestNode(i + 1);
		addAtFront(list1, node);
	}
	for (i = 0; i < numNodes; i++) {
		node = createTestNode(i + 1);
		addAtRear(list2, node);
	}

	test1 = list1->head;
	test2 = list2->head;
	for (i = 0; i < numNodes; i++) {
		if (test1 == NULL || test2 == NULL )
			break;

		myassert(testlist->compareTo(test1->obj, test2->obj) == FALSE)
		test1 = test1->next;
		test2 = test2->next;
	}

	reverseList(list2);

	test1 = list1->head;
	test2 = list2->head;
	for (i = 0; i < numNodes; i++) {
		if (test1 == NULL || test2 == NULL )
			break;

		myassert(testlist->compareTo(test1->obj, test2->obj) == TRUE)
		test1 = test1->next;
		test2 = test2->next;
	}

	freeList(list1);
	freeList(list2);
	return TRUE;
}

Boolean testSearch() {
	initialize();

	NodePtr testNode = createTestNode(30);
	NodePtr node1 = createTestNode(1);
	NodePtr node2 = createTestNode(2);
	NodePtr node3 = createTestNode(3);
	NodePtr node4 = createTestNode(4);
	NodePtr node5 = createTestNode(5);
	NodePtr node6 = createTestNode(6);
	NodePtr node7 = createTestNode(7);
	NodePtr node8 = createTestNode(8);
	NodePtr node9 = createTestNode(9);

	addAtFront(testlist, node1);
	addAtFront(testlist, node2);
	addAtFront(testlist, node3);
	addAtFront(testlist, node4);
	addAtFront(testlist, node5);
	addAtFront(testlist, testNode);
	addAtFront(testlist, node6);
	addAtFront(testlist, node7);
	addAtFront(testlist, node8);
	addAtFront(testlist, node9);

	NodePtr searchNode;
	searchNode = search(testlist, testNode->obj);

	myassert(testlist->compareTo(searchNode, testNode) == TRUE);

	return TRUE;
}

// Driver
void runUnitTests() {
	Boolean result;
	char *testName;

	testName = "addAtFrontWithNoNodes";
	beforeTest(testName);
	result = addAtFrontWithNoNodes();
	afterTest(testName, result);

	testName = "addAtFrontWithOneNode";
	beforeTest(testName);
	result = addAtFrontWithOneNode();
	afterTest(testName, result);

	testName = "addAtRearWithNoNodes";
	beforeTest(testName);
	result = addAtRearWithNoNodes();
	afterTest(testName, result);

	testName = "addAtRearWithOneNode";
	beforeTest(testName);
	result = addAtRearWithOneNode();
	afterTest(testName, result);

	testName = "removeFromFrontWithNoNode";
	beforeTest(testName);
	result = removeFromFrontWithNoNode();
	afterTest(testName, result);

	testName = "removeFromFrontWithOneNode";
	beforeTest(testName);
	result = removeFromFrontWithOneNode();
	afterTest(testName, result);

	testName = "removeFromFrontWithManyNodes";
	beforeTest(testName);
	result = removeFromFrontWithManyNodes();
	afterTest(testName, result);

	testName = "removeFromRearWithNoNode";
	beforeTest(testName);
	result = removeFromRearWithNoNode();
	afterTest(testName, result);

	testName = "removeFromRearWithOneNode";
	beforeTest(testName);
	result = removeFromRearWithOneNode();
	afterTest(testName, result);

	testName = "removeFromRearWithManyNodes";
	beforeTest(testName);
	result = removeFromRearWithManyNodes();
	afterTest(testName, result);

	testName = "removeFromListWithNoNode";
	beforeTest(testName);
	result = removeFromListWithNoNode();
	afterTest(testName, result);

	testName = "removeFromListWithOneNode";
	beforeTest(testName);
	result = removeFromListWithOneNode();
	afterTest(testName, result);

	testName = "removeFromListWithManyNodes";
	beforeTest(testName);
	result = removeFromListWithManyNodes();
	afterTest(testName, result);

	testName = "addNullNodeToFront";
	beforeTest(testName);
	result = addNullNodeToFront();
	afterTest(testName, result);

	testName = "addNullNodeToRear";
	beforeTest(testName);
	result = addNullNodeToRear();
	afterTest(testName, result);

	testName = "testIsEmpty";
	beforeTest(testName);
	result = testIsEmpty();
	afterTest(testName, result);

	testName = "testReverse";
	beforeTest(testName);
	result = testReverse();
	afterTest(testName, result);

	testName = "testSearch";
	beforeTest(testName);
	result = testSearch();
	afterTest(testName, result);

	fprintf(stdout, "Test Cases: %d\n", testCount);
	fprintf(stdout, "Passed: %d\n", passCount);
	fprintf(stdout, "Failed: %d\n", testCount - passCount);
}

// Insertion
int main(int argc, char *argv[]) {
// Setup and run
	initialize();
	runUnitTests();

// Close and free all the things!
	freeList(testlist);
	exit(0);
}
