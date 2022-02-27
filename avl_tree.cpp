#include <iostream>
using namespace std;

template <class T>
class node
{
public:
    T value;
    node *left, *right;
    int height, count;
    int count_left, count_right;

    node(T key)
        : value(key), left(NULL), right(NULL), height(1), count(1),
          count_left(0), count_right(0) {}
};

template <class T>
class student
{
private:
    int roll;
    string name;

public:
    student()
        : roll(-1), name("std") {}

    student(int rollnum, string naam)
        : roll(rollnum), name(naam) {}

    bool operator<(student const &s1)
    {
        if (this->roll < s1.roll)
            return true;
        else if (this->roll == s1.roll && this->name < s1.name)
            return true;
        else
            return false;
    }

    bool operator>(student const &s1)
    {
        if (this->roll > s1.roll)
            return true;
        else if (this->roll == s1.roll && this->name > s1.name)
            return true;
        else
            return false;
    }

    bool operator==(student const &s1)
    {
        if (this->roll == s1.roll && this->name == s1.name)
            return true;
        else
            return false;
    }

    bool operator>=(student const &s1)
    {
        if (this->roll > s1.roll)
            return true;
        else if (this->roll == s1.roll && this->name > s1.name)
            return true;
        else if (this->roll == s1.roll && this->name == s1.name)
            return true;
        else
            return false;
    }

    bool operator<=(student const &s1)
    {
        if (this->roll < s1.roll)
            return true;
        else if (this->roll == s1.roll && this->name < s1.name)
            return true;
        else if (this->roll == s1.roll && this->name == s1.name)
            return true;
        else
            return false;
    }
};

template <class T>
class avl
{
public:
    node<T> *root;
    int size;

    avl()
        : root(NULL), size(0) {}

    int height_node(node<T> *node)
    {
        if (node == NULL)
            return 0;

        return node->height;
    }

    int height_bal(node<T> *root)
    {
        if (root == NULL)
            return 0;

        int h_left = height_node(root->left);
        int h_right = height_node(root->right);

        return (h_left - h_right);
    }

    void change_count(node<T> *root)
    {
        int count_r, count_l;

        if (root->right)
        {
            count_r = root->right->count_right + root->right->count_left + root->right->count;
        }
        else
            count_r = 0;

        if (root->left)
        {
            count_l = root->left->count_right + root->left->count_left + root->left->count;
        }
        else
            count_l = 0;

        root->count_left = count_l;
        root->count_right = count_r;
    }

    void update_height(node<T> *root)
    {
        int root_l_height, root_r_height;

        if (root->left)
            root_l_height = root->left->height;
        else
            root_l_height = 0;

        if (root->right)
            root_r_height = root->right->height;
        else
            root_r_height = 0;

        root->height = max(root_l_height, root_r_height) + 1;
    }

    T max_val(node<T> *root)
    {
        while (root->right != NULL)
            root = root->right;

        return root->value;
    }

    T min_val(node<T> *root)
    {
        while (root->left != NULL)
            root = root->left;

        return root->value;
    }

    int great_equal(T key)
    {
        int count{0};
        node<T> *temp = root;

        while (temp)
        {
            if (temp->value >= key)
            {
                count += (temp->count + temp->count_right);
                temp = temp->left;
            }
            else if (temp->value < key)
                temp = temp->right;
        }
        return count;
    }

    int less_equal(T key)
    {
        int count{0};
        node<T> *temp = root;

        while (temp)
        {
            if (temp->value <= key)
            {
                count += (temp->count + temp->count_left);
                temp = temp->right;
            }
            else if (temp->value > key)
                temp = temp->left;
        }
        return count;
    }

    node<T> *LL(node<T> *root);
    node<T> *RR(node<T> *root);
    node<T> *LR(node<T> *root);
    node<T> *RL(node<T> *root);

    node<T> *do_insert(node<T> *root, T key);
    node<T> *insert(T key);

    node<T> *do_delete(node<T> *root, T key);
    void delete_node(T key);

    bool search(T key);

    void num_nodes(node<T> *root, T key, int &num);
    int count(T key);

    T lower_bound_key(T key);
    T upper_bound_key(T key);

    T closest_element(T key);

    void k_find(node<T> *root, int k, int &count, bool &flag);
    void k_th_largest(int k);

    int count_in_range(T key1, T key2);
};

template <class T>
node<T> *avl<T>::LL(node<T> *root)
{
    //RIGHT ROTATE
    //rotations
    node<T> *y = root->left;
    node<T> *T3 = y->right;

    y->right = root;
    root->left = T3;

    //updations (height)
    int root_l_height = height_node(root->left);
    int root_r_height = height_node(root->right);
    root->height = max(root_l_height, root_r_height) + 1;

    int y_l_height = height_node(y->left);
    int y_r_height = height_node(y->right);
    y->height = max(y_l_height, y_r_height) + 1;

    //updations (count)
    change_count(y);
    change_count(root);

    return y;
}

template <class T>
node<T> *avl<T>::RR(node<T> *root)
{
    //LEFT ROTATE
    //rotations
    node<T> *y = root->right;
    node<T> *T2 = y->left;
    y->left = root;
    root->right = T2;

    //updations (height)
    int y_l_height = height_node(y->left);
    int y_r_height = height_node(y->right);
    y->height = max(y_l_height, y_r_height) + 1;

    int root_l_height = height_node(root->left);
    int root_r_height = height_node(root->right);
    root->height = max(root_l_height, root_r_height) + 1;

    //updations(count)
    change_count(y);
    change_count(root);

    return y;
}

template <class T>
node<T> *avl<T>::LR(node<T> *root)
{
    //LEFT-RIGHT ROTATE
    root->left = RR(root->left);
    return LL(root);
}

template <class T>
node<T> *avl<T>::RL(node<T> *root)
{
    //RIGHT-LEFT ROTATE
    root->right = LL(root->right);
    return RR(root);
}

template <class T>
node<T> *avl<T>::do_insert(node<T> *root, T key)
{
    //first node
    if (root == NULL)
    {
        node<T> *new_node = new node<T>(key);
        // cout << "First_node inserted" << endl;
        return new_node;
    }

    //BST Insertions
    else if (key < root->value)
    {
        root->left = do_insert(root->left, key);
    }
    else if (key == root->value)
    {
        //already present, increasing count
        root->count++;
        return root;
    }
    else if (key > root->value)
    {
        root->right = do_insert(root->right, key);
    }

    //Updating heights
    update_height(root);

    //Cases for unbalanced node
    int bal_factor = height_bal(root);
    if (bal_factor > 1)
    {
        if (key < root->left->value)
        {
            //LL Case
            return LL(root);
        }
        if (key > root->left->value)
        {
            //LR Case
            return LR(root);
        }
    }
    else if (bal_factor < -1)
    {
        if (key < root->right->value)
        {
            //RL Case
            return RL(root);
        }
        if (key > root->right->value)
        {
            //RR Case
            return RR(root);
        }
    }

    update_height(root);
    change_count(root);
    return root;
}

template <class T>
node<T> *avl<T>::insert(T key)
{
    node<T> *top = do_insert(root, key);
    size++;
    return top;
}

template <class T>
node<T> *avl<T>::do_delete(node<T> *root, T key)
{
    if (root == NULL)
        return root;

    if (key < root->value)
    {
        //delete on left_subtree
        root->left = do_delete(root->left, key);
    }
    else if (key > root->value)
    {
        //delete on right_subtree
        root->right = do_delete(root->right, key);
    }
    else
    {
        //this node is to be deleted
        if (root->left == NULL && root->right == NULL)
        {
            //node has 0 children (leaf node)
            if (root->count == 1)
            {
                delete (root);
                return NULL;
            }
            else
            {
                //duplicate node
                root->count--;
            }
        }
        else if (root->left == NULL || root->right == NULL)
        {
            //node has 1 child
            node<T> *child;

            if (root->left != NULL)
                child = root->left;
            else
                child = root->right;

            if (root->count == 1)
            {
                *root = *child;
                delete (child);
                return root;
            }
            else
            {
                //duplicate node
                root->count--;
            }
        }
        else
        {
            //node has two chilren
            //remove and replace with inorder successor
            if (root->count == 1)
            {
                node<T> *in_successor = root->right;
                while (in_successor->left)
                    in_successor = in_successor->left;

                //copying and deleting it
                root->value = in_successor->value;
                root->right = do_delete(root->right, in_successor->value);
            }
            else
            {
                //duplicate node
                root->count--;
            }
        }
    }
    if (root == NULL)
        return root;

    //Updating heights
    update_height(root);

    //Cases for unbalanced node
    int bal_factor = height_bal(root);
    if (bal_factor > 1)
    {
        int l_bal_factor = height_bal(root->left);
        if (l_bal_factor >= 0)
        {
            //LL Case
            return LL(root);
        }
        else if (l_bal_factor < 0)
        {
            //LR Case
            return LR(root);
        }
    }
    else if (bal_factor < -1)
    {
        int r_bal_factor = height_bal(root->right);
        if (r_bal_factor > 0)
        {
            //RL Case
            return RL(root);
        }
        else if (r_bal_factor <= 0)
        {
            //RR Case
            return RR(root);
        }
    }
    change_count(root);
    return root;
}

template <class T>
void avl<T>::delete_node(T key)
{
    node<T> *down = do_delete(root, key);
    size--;
    return;
}

template <class T>
bool avl<T>::search(T key)
{
    node<T> *temp = root;

    while (temp)
    {
        if (key < temp->value)
            temp = temp->left;

        if (!temp)
            break;

        if (key == temp->value)
            break;

        if (!temp)
            break;

        if (key > temp->value)
            temp = temp->right;

        if (!temp)
            break;
    }

    if (temp)
        return true;
    else
        return false;
}

template <class T>
void avl<T>::num_nodes(node<T> *root, T key, int &num)
{
    if (root == NULL)
        return;

    T node_value = root->value;

    if (root == NULL)
        return;
    else if (key < node_value)
    {
        num_nodes(root->left, key, num);
    }
    else if (key > node_value)
    {
        num_nodes(root->right, key, num);
    }
    else if (key == node_value)
    {
        num = root->count;
        return;
    }
    else
    {
        num = 0;
        return;
    }
}

template <class T>
int avl<T>::count(T key)
{
    int occurences{0};
    num_nodes(this->root, key, occurences);

    return occurences;
}

template <class T>
T avl<T>::lower_bound_key(T key)
{
    node<T> *temp = this->root;

    T min_value = min_val(temp);
    T max_value = max_val(temp);
    T node_value = temp->value;
    T lower_bound;

    if (key < min_value)
        return min_value;

    if (key >= min_value && key <= max_value)
    {
        while (temp)
        {
            if (key < node_value)
            {
                lower_bound = node_value;
                temp = temp->left;
            }
            else if (key == node_value)
            {
                lower_bound = key;
                break;
            }
            else
            {
                //key > node_value
                //skip
                temp = temp->right;
            }
        }
        return lower_bound;
    }
    else
    {
        cout << "-1" << endl;
        //return -1;
        exit(0);
    }
}

template <class T>
T avl<T>::upper_bound_key(T key)
{
    node<T> *temp = this->root;

    T min_value = min_val(temp);
    T max_value = max_val(temp);
    T upper_bound = max_value;

    if (key < min_value)
        return min_value;

    if (key >= min_value && key <= max_value)
    {
        while (temp)
        {
            if (key < temp->value)
            {
                upper_bound = temp->value;
                temp = temp->left;
            }
            else
            {
                //key > node_value
                //skip
                temp = temp->right;
            }
        }
        return upper_bound;
    }
    else
    {
        cout << "Upper_bound doesn't exist" << endl;
        //return -1;
        exit(0);
    }
}

template <class T>
T avl<T>::closest_element(T key)
{
    node<T> *temp = this->root;

    T min_value = min_val(temp);
    T max_value = max_val(temp);

    if (key < min_value)
        return min_value;
    if (key > max_value)
        return max_value;

    T greater, lesser;
    T closest_element;

    while (temp)
    {
        if (key < temp->value)
        {
            greater = temp->value;
            temp = temp->left;
        }
        else if (key == temp->value)
        {
            greater = key;
            break;
        }
        else if (key > temp->value)
        {
            lesser = temp->value;
            temp = temp->right;
        }
    }

    if ((key - lesser) > (greater - key))
        return greater;
    else
        return lesser;
}

template <class T>
void avl<T>::k_find(node<T> *root, int k, int &count, bool &flag)
{
    if (count >= k)
        return;
    if (root == NULL)
        return;

    k_find(root->right, k, count, flag);

    count += root->count;
    if (count >= k && flag == false)
    {
        flag = true;
        cout << root->value << endl;
        return;
    }

    k_find(root->left, k, count, flag);
}

template <class T>
void avl<T>::k_th_largest(int k)
{
    int count{0};
    bool flag{false};

    k_find(root, k, count, flag);
}

template <class T>
int avl<T>::count_in_range(T key1, T key2)
{
    if (key1 > key2)
        return 0;

    int count{0};

    int tot_count = size;
    //cout << tot_count << endl;

    int great_equal_key1 = great_equal(key1);
    int less_equal_key2 = less_equal(key2);

    count = (great_equal_key1 + less_equal_key2) - tot_count;

    return count;
}

int main()
{

    int q;
    cin >> q;
    avl<int> tree;

    while (q--)
    {
        int option;
        cin >> option;
        int input, count;
        int x, y, z, a, b;
        bool find;

        switch (option)
        {

        case 1:
            cin >> input;
            tree.root = tree.insert(input);
            break;

        case 2:
            cin >> input;
            tree.delete_node(input);
            break;

        case 3:
            cin >> input;
            find = tree.search(input);
            cout << ((find == 0) ? "0" : "1") << endl;
            break;

        case 4:
            cin >> input;
            count = tree.count(input);
            cout << count << endl;
            break;

        case 5:
            cin >> input;
            x = tree.lower_bound_key(input);
            cout << x << endl;
            break;

        case 6:
            cin >> input;
            y = tree.upper_bound_key(input);
            cout << y << endl;
            break;

        case 7:
            cin >> input;
            z = tree.closest_element(input);
            cout << z << endl;
            break;

        case 8:
            cin >> input;
            tree.k_th_largest(input);
            break;

        case 9:
            cin >> input;
            cin >> a;
            cin >> b;
            count = tree.count_in_range(a, b);
            cout << count << endl;
            break;
        }
    }

    // int q;
    // cin >> q;
    // avl<string> tree;

    // while (q--)
    // {
    //     int option;
    //     cin >> option;
    //     string input;
    //     string x, y, z, a, b;
    //     int count, k;
    //     bool find;

    //     switch (option)
    //     {

    //     case 1:
    //         cin >> input;
    //         tree.root = tree.insert(input);
    //         break;

    //     case 2:
    //         cin >> input;
    //         tree.delete_node(input);
    //         break;

    //     case 3:
    //         cin >> input;
    //         find = tree.search(input);
    //         cout << ((find == 0) ? "0" : "1") << endl;
    //         break;

    //     case 4:
    //         cin >> input;
    //         count = tree.count(input);
    //         cout << count << endl;
    //         break;

    //     case 5:
    //         cin >> input;
    //         x = tree.lower_bound_key(input);
    //         cout << x << endl;
    //         break;

    //     case 6:
    //         cin >> input;
    //         y = tree.upper_bound_key(input);
    //         cout << y << endl;
    //         break;

    //     case 8:
    //         cin >> k;
    //         tree.k_th_largest(k);
    //         break;

    //     case 9:
    //         cin >> input;
    //         cin >> a;
    //         cin >> b;
    //         count = tree.count_in_range(a, b);
    //         cout << count << endl;
    //         break;
    //     }
    // }

    // avl<int> tree;

    // while (true)
    // {
    //     cout << "\nEnter the integer to perform respective function : \n"
    //          << "1. INSERT\n"
    //          << "2. DELETE\n"
    //          << "3. SEARCH\n"
    //          << "4. COUNT\n"
    //          << "5. LOWER_BOUND\n"
    //          << "6. UPPER_BOUND\n"
    //          << "7. NEAREST (to some value)\n"
    //          << "8. Kth GREATEST\n"
    //          << "9. COUNT IN RANGE [a,b] \n";

    //     cout << "Option : ";
    //     int option;
    //     cin >> option;

    //     int input, count;
    //     int x, y, z, a, b;
    //     bool find;
    //     switch (option)
    //     {
    //     case 1:
    //         cout << "Enter what to insert : ";
    //         cin >> input;
    //         tree.root = tree.insert(input);
    //         break;

    //     case 2:
    //         cout << "Enter what to delete : ";
    //         cin >> input;
    //         tree.delete_node(input);
    //         break;

    //     case 3:
    //         cout << "Enter what to search : ";
    //         cin >> input;
    //         find = tree.search(input);
    //         cout << ((find == 0) ? "Not Found" : "Found") << endl;
    //         break;

    //     case 4:
    //         cout << "Enter what to count : ";
    //         cin >> input;
    //         count = tree.count(input);
    //         cout << "Count: " << count << endl;
    //         break;

    //     case 5:
    //         cout << "Enter whose lower_bound to find : ";
    //         cin >> input;
    //         x = tree.lower_bound_key(input);
    //         cout << "Lower Bound : " << x << endl;
    //         break;

    //     case 6:
    //         cout << "Enter whose upper_bound to find : ";
    //         cin >> input;
    //         y = tree.upper_bound_key(input);
    //         cout << "Upper Bound : " << y << endl;
    //         break;

    //     case 7:
    //         cout << "Enter whose closest_element to find : ";
    //         cin >> input;
    //         z = tree.closest_element(input);
    //         cout << "Closest Element : " << z << endl;
    //         break;

    //     case 8:
    //         cout << "Enter k to find kth largest in tree : ";
    //         cin >> input;
    //         cout << input << "th Largest : ";
    //         tree.k_th_largest(input);
    //         break;

    //     case 9:
    //         cout << "Enter range (a, b)  : ";
    //         cin >> a;
    //         cin >> b;
    //         count = tree.count_in_range(a, b);
    //         cout << "Range count : " << count << endl;
    //         break;
    //     }
    // }

    // avl<string> tree;

    // while (true)
    // {
    //     cout << "\nEnter the integer to perform respective function : \n"
    //          << "1. INSERT\n"
    //          << "2. DELETE\n"
    //          << "3. SEARCH\n"
    //          << "4. COUNT\n"
    //          << "5. LOWER_BOUND\n"
    //          << "6. UPPER_BOUND\n"
    //          << "7. Kth GREATEST\n"
    //          << "8. COUNT IN RANGE [a,b] \n";

    //     cout << "Option : ";
    //     int option;
    //     cin >> option;

    //     string input;
    //     string x, y, z, a, b;
    //     int count, k;
    //     bool find;
    //     switch (option)
    //     {
    //     case 1:
    //         cout << "Enter what to insert : ";
    //         cin >> input;
    //         tree.root = tree.insert(input);
    //         break;

    //     case 2:
    //         cout << "Enter what to delete : ";
    //         cin >> input;
    //         tree.delete_node(input);
    //         break;

    //     case 3:
    //         cout << "Enter what to search : ";
    //         cin >> input;
    //         find = tree.search(input);
    //         cout << ((find == 0) ? "Not Found" : "Found") << endl;
    //         break;

    //     case 4:
    //         cout << "Enter what to count : ";
    //         cin >> input;
    //         count = tree.count(input);
    //         cout << "Count: " << count << endl;
    //         break;

    //     case 5:
    //         cout << "Enter whose lower_bound to find : ";
    //         cin >> input;
    //         x = tree.lower_bound_key(input);
    //         cout << "Lower Bound : " << x << endl;
    //         break;

    //     case 6:
    //         cout << "Enter whose upper_bound to find : ";
    //         cin >> input;
    //         y = tree.upper_bound_key(input);
    //         cout << "Upper Bound : " << y << endl;
    //         break;

    //     case 7:
    //         cout << "Enter k to find kth largest in tree : ";
    //         cin >> k;
    //         cout << k << "th Largest : ";
    //         tree.k_th_largest(k);
    //         break;

    //     case 8:
    //         cout << "Enter range (a, b)  : ";
    //         cin >> a;
    //         cin >> b;
    //         count = tree.count_in_range(a, b);
    //         cout << "Range count : " << count << endl;
    //         break;
    //     }
    // }

    return 0;
}