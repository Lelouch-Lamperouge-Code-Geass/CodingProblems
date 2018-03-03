You are given a tree which represents the hierarchy of a company. The root node represents the CEO.

All the people in this company can be represented as an Employee class:

```cpp
class Employee {
private:
	int m_id;
	string m_name;
	vector<Employee*> m_reports;
public:
	vector<Employee*> getReports() {
		return m_reports;
	}
	int getId() {
		return m_id;
	}
	string getName() {
		return m_name;
	}
};
```

Here, ```m_reports``` stores the direct subordinates of the employee. Hence this employee can be said as the manager of all the instances in ```m_reports```.

Right now, write a function to return the lowest common manager of two employees.


# Solution

```cpp

Employee* findCommonManager(Employee *cur_employee, Employee *employee_one, Employee *employee_two) {
	if (!cur_employee || cur_employee == employee_one || cur_employee == employee_two) return cur_employee;
	bool is_managing_employee_one(false), is_managing_employee_two(false);

	for (Employee *temp_report : cur_employee->getReports()) {
		Employee* temp_manager = findCommonManager(temp_report, employee_one, employee_two);

		if (temp_manager == employee_one) {
			is_managing_employee_one = true;
		} else if (temp_manager == employee_two) {
			is_managing_employee_two = true;
		} else if (temp_manager) {
      			return temp_manager;
    		}
	}

	if (is_managing_employee_one && is_managing_employee_two) {
		return cur_employee;
	}
	else {
		if (is_managing_employee_one) return employee_one;
		else if (is_managing_employee_two) return employee_two;
		else return nullptr;
	}
}

```
