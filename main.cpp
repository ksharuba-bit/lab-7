#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>

using namespace std;

class Function {
public:
    Function() = default;
    virtual ~Function() = default;

    virtual double calculate(double x) const = 0;
    virtual string type() const = 0;
    virtual void print() const = 0;
    virtual void edit() = 0;
};

class LinearFunction : public Function {
private:
    double a;
    double b;

public:
    LinearFunction() : a(0.0), b(0.0) {}
    LinearFunction(double aValue, double bValue) : a(aValue), b(bValue) {}

    double calculate(double x) const override {
        return a * x + b;
    }

    string type() const override {
        return "linear";
    }

    void print() const override {
        cout << "Linear: y = " << a << "x";
        if (b >= 0) cout << " + " << b;
        else cout << " - " << -b;
        cout << '\n';
    }

    void edit() override {
        cin >> a >> b;
    }
};

class QuadraticFunction : public Function {
private:
    double a;
    double b;
    double c;

public:
    QuadraticFunction() : a(0.0), b(0.0), c(0.0) {}
    QuadraticFunction(double aValue, double bValue, double cValue)
        : a(aValue), b(bValue), c(cValue) {}

    double calculate(double x) const override {
        return a * x * x + b * x + c;
    }

    string type() const override {
        return "quadratic";
    }

    void print() const override {
        cout << "Quadratic: y = " << a << "x^2";
        if (b >= 0) cout << " + " << b << "x";
        else cout << " - " << -b << "x";
        if (c >= 0) cout << " + " << c;
        else cout << " - " << -c;
        cout << '\n';
    }

    void edit() override {
        cin >> a >> b >> c;
    }
};

class CubicFunction : public Function {
private:
    double a;
    double b;
    double c;
    double d;

public:
    CubicFunction() : a(0.0), b(0.0), c(0.0), d(0.0) {}
    CubicFunction(double aValue, double bValue, double cValue, double dValue)
        : a(aValue), b(bValue), c(cValue), d(dValue) {}

    double calculate(double x) const override {
        return a * x * x * x + b * x * x + c * x + d;
    }

    string type() const override {
        return "cubic";
    }

    void print() const override {
        cout << "Cubic: y = " << a << "x^3";
        if (b >= 0) cout << " + " << b << "x^2";
        else cout << " - " << -b << "x^2";
        if (c >= 0) cout << " + " << c << "x";
        else cout << " - " << -c << "x";
        if (d >= 0) cout << " + " << d;
        else cout << " - " << -d;
        cout << '\n';
    }

    void edit() override {
        cin >> a >> b >> c >> d;
    }
};

void showAll(const vector<unique_ptr<Function>>& functions) {
    if (functions.empty()) {
        cout << "No records.\n";
        return;
    }

    for (size_t i = 0; i < functions.size(); ++i) {
        cout << i + 1 << ". ";
        functions[i]->print();
    }
}

void searchByType(const vector<unique_ptr<Function>>& functions, const string& wanted) {
    bool found = false;
    for (size_t i = 0; i < functions.size(); ++i) {
        if (functions[i]->type() == wanted) {
            cout << i + 1 << ". ";
            functions[i]->print();
            found = true;
        }
    }
    if (!found) cout << "Nothing found.\n";
}

int main() {
    vector<unique_ptr<Function>> functions;

    cout << fixed << setprecision(2);

    while (true) {
        cout << "\nMENU\n"
             << "1 - Add linear function\n"
             << "2 - Add quadratic function\n"
             << "3 - Add cubic function\n"
             << "4 - Show all\n"
             << "5 - Search by type\n"
             << "6 - Edit record\n"
             << "7 - Calculate value\n"
             << "0 - Exit\n"
             << "Choice: ";

        int choice;
        if (!(cin >> choice)) break;

        if (choice == 0) break;

        if (choice == 1) {
            double a, b;
            cout << "Enter a b: ";
            cin >> a >> b;
            functions.push_back(make_unique<LinearFunction>(a, b));
        }
        else if (choice == 2) {
            double a, b, c;
            cout << "Enter a b c: ";
            cin >> a >> b >> c;
            functions.push_back(make_unique<QuadraticFunction>(a, b, c));
        }
        else if (choice == 3) {
            double a, b, c, d;
            cout << "Enter a b c d: ";
            cin >> a >> b >> c >> d;
            functions.push_back(make_unique<CubicFunction>(a, b, c, d));
        }
        else if (choice == 4) {
            showAll(functions);
        }
        else if (choice == 5) {
            string wanted;
            cout << "Type (linear/quadratic/cubic): ";
            cin >> wanted;
            searchByType(functions, wanted);
        }
        else if (choice == 6) {
            size_t index;
            cout << "Record number: ";
            cin >> index;
            if (index == 0 || index > functions.size()) {
                cout << "Invalid record number.\n";
                continue;
            }

            cout << "Enter new coefficients for "
                 << functions[index - 1]->type()
                 << ": ";
            functions[index - 1]->edit();
            cout << "Record updated.\n";
        }
        else if (choice == 7) {
            size_t index;
            double x;
            cout << "Record number and x: ";
            cin >> index >> x;
            if (index == 0 || index > functions.size()) {
                cout << "Invalid record number.\n";
                continue;
            }
            cout << "y(" << x << ") = "
                 << functions[index - 1]->calculate(x)
                 << '\n';
        }
        else {
            cout << "Unknown menu item.\n";
        }
    }

    return 0;
}
