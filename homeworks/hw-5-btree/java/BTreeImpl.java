public class BTreeImpl extends BTree {

	public BTreeImpl(int order) {
		super(order);
	}

	public void split (Node curNode) {
		
	}
	
	public void sort(int[] arr) {
		boolean notDone = true;
		while (notDone) {
			notDone = false;
			for (int i = 0; i<arr.length-1; i++) {
				if(arr[i] > arr[i+1]) {
					int temp = arr[i];
					arr[i]=arr[i+1];
					arr[i+1] = temp;
					notDone = true;
				}
			}
		}
	}
	
	public void insert(int key) {
		// Checks root for key
		for (int i = 0; i < root.numKeys; i++) {
			if (root.getKeys()[i] == key) {
				return;
			}
		}
		// Inserts if root is a leaf
		if (root.isLeaf) {
			root.getKeys()[root.numKeys] = key;
			sort(root.getKeys());
			root.numKeys++;
			if (root.numKeys == 5) {
				split(root);
			}
			return;
		}
		// Traverses down tree
		boolean done = false;
		while (!done) {
			for (int j = 0; j < root.numKeys; j++) {
				if (key < root.getKeys()[j]) {
					done = true;
					insertKey(root.getChildren()[j], key);
				}
			}
			done = true;
			insertKey(root.getChildren()[root.numKeys + 1], key);
		}
	}

	public void insertKey(Node curNode, int key) {
		for (int i = 0; i < curNode.numKeys; i++) {
			if (root.getKeys()[i] == key) {
				return;
			}
		}
		if (curNode.isLeaf) {
			curNode.getKeys()[curNode.numKeys] = key;
			sort(curNode.getKeys());
			curNode.numKeys++;
			if (curNode.numKeys == 5) {
				split(curNode);
			}
			return;
		}
		// Traverses down tree
		boolean done = false;
		while (!done) {
			for (int j = 0; j < curNode.numKeys; j++) {
				if (key < curNode.getKeys()[j]) {
					done = true;
					insertKey(curNode.getChildren()[j], key);
				}
			}
			done = true;
			insertKey(curNode.getChildren()[curNode.numKeys + 1], key);
		}
	}

	public void remove(int key) {
		
	}

	public boolean contains(int key) {
		return checkKey(root, key);
	}

	public boolean checkKey(Node curNode, int key) {
		for (int i = 0; i < curNode.numKeys; i++) {
			if (curNode.getKeys()[i] == key) {
				return true;
			}
		}
		if (!curNode.isLeaf) {
			boolean done = false;
			while (!done) {
				for (int j = 0; j < curNode.numKeys; j++) {
					if (key < curNode.getKeys()[j]) {
						done = true;
						return checkKey(curNode.getChildren()[j], key);
					}
				}
				done = true;
				return checkKey(curNode.getChildren()[curNode.numKeys], key);
			}
		}
		return false;
	}
}
