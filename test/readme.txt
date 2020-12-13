--RUN TEST:
	_ copy BKUTree.cpp into folder ./mywork
	_ modify your directories
	_ use the Checking.cpp to check the answer

###############################################################
NOTE THAT THE THREE TEST SETS ARE NOT DIFFERENT AT ALL

--DEBUGING TOOL:
	_ printStructure() provided

--TESTING: (using TRY CATCH)
	_ AVLTree:
		+ add: print NLR struct after adding + "Duplicate key"
		+ remove: print NLR struct after removing + "Not found"
		+ search: "Not found"
	_ SplayTree:
		+ add: print NLR struct after adding + "Duplicate key"
		+ remove: print NLR struct after removing + "Not found"
		+ search: "Not found"
	_ BKUTree:
		+ add: use displayTree()
		+ remove: use displayTree()
		+ search: use traversedList vector

--DISTRIBUTION:
----size:	
	_ small tests (10 nodes) for basic-fault detecting
		+ add 10 nodes with random key
		+ search 5 random keys
		+ remove 10 nodes in random order
	_ medium tests (20 nodes)
		+ add 20 nodes with random key
		+ search 10 random keys
		+ remove 20 nodes in random order
	_ big tests (100 nodes) for deeper insight
		+ add 100 nodes with random key
		+ search 50 random keys
		+ remove 100 nodes in random order
----type:	
	_ AVL: 100 tests
	_ Splay: 200 tests 	
	_ BKU: 5000 tests
----so:	
	_ AVL: 100 - 200 - 200
	_ Splay: 200 - 300 - 500
	_ BKU: 500 - 1500 - 5000

--CONVENTION for testcases:
	a: choose a tree AVL | Splay | BKU
	b: choose a test size 10 | 20 | 100
_ first line: a b
_ next b line (depending on size): insert key
_ next b/4 line: duplicate insert key
_ next b/2 line: search key
_ next b/4 line: search not found key
_ next b/4 line: delete not found key
_ next b line: delete key
