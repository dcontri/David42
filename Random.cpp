#include "Random.hpp"

void pprint(const std::vector<std::string>& vec) {
	for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << std::endl;
}

Random::Random(std::string list) {
	this->userList = ft_split(list, ' ');
	for (size_t i = 0; i < userList.size(); i++) {
		size_t j = i;
		plus(j, userList);
		while (j != i) {
			if (userList[j] == userList[i]) {
				userList.erase(userList.begin() + j);
				if (j < i) {
					j--;
					i--;
				} else
					j--;
			}
			plus(j, userList);
		}
	}
}

Random::~Random() {}

void	Random::randomize() {
	std::srand(std::time(0));
	final.clear();
	while (true) {
		final.clear();
		final.push_back(userList);
		for (int i = 0; i < 2; i++) {
			std::vector<std::string> copy = scrumble(userList);
			std::vector<std::string> temp;
			for (size_t y = 0; y < userList.size(); y++)
			{
				noLoop(copy.size());
				size_t j;
				if (copy.size() -1 != 0)
					j = std::rand() % (copy.size() -1);
				else
					j = 0;
				//std::cout << "------------\n" << "DEBUG(1): " << copy[j] << std::endl;
				while (!checkIsIn(copy[j], usedTo) && noLoop(0) && usedTo.size() != 0)
					plus(j, copy);
				noLoop(copy.size());
				//std::cout << "DEBUG(2): " << copy[j] << std::endl;
				while ((checkGroup(final, y, copy[j]) || checkUsedTo(final, y, copy[j])) && noLoop(0))
					plus(j, copy);
				//std::cout << "DEBUG(3): " << copy[j] << std::endl;
				temp.push_back(copy[j]);
				copy.erase(copy.begin() + j);
				//std::cout << "\n======================" << std::endl;
				//pprint(copy);
				//std::cout << "======================" << std::endl;
				//pprint(temp);
				//std::cout << "======================\n" << std::endl;
			}
			final.push_back(temp);
		}
		if (checkScrumble()) break;
	}
}

std::vector<std::string>	Random::scrumble(std::vector<std::string> vector) {
	std::srand(std::time(0));
	std::vector<std::string>	ret = vector;
	std::string					temp;
	size_t						j;
	if (vector.size() -1 != 0)
		return ret;
	for (size_t i = 0; i < vector.size(); i++) {
		j = std::rand() % (vector.size() -1);
		temp = ret[j];
		ret[j] = ret[i];
		ret[i] = temp;
	}
	return  ret;
}

bool	Random::addUser(std::string name) {
	name = trim_non_alpha(name); 
	if (checkIsIn(name, userList))
		return false;
	if (!name.empty())
		userList.push_back(name);
	else
		return false;
	return true;
}

bool	Random::addUsedTo(std::string name) {
	name = trim_non_alpha(name);
	pprint(usedTo);
	if (checkIsIn(name, usedTo) || !checkIsIn(name, userList))
		return false;
	if (!name.empty())
		usedTo.push_back(name);
	else
		return false;
	return true;
}

bool	Random::noLoop(int n) {
	if (n > 0) {
		loop = n;
		return true;
	}
	if (n == 0)
		loop--;
	if (loop <= 0)
		return false;
	else
		return true;
}

void	Random::plus(size_t &i, std::vector<std::string> arr) {
	i++;
	if (i == arr.size())
		i = 0;
}

bool	Random::checkScrumble() {
	for (size_t y = 0; y < final[0].size(); y++)
		for (size_t j = 0; j < final.size(); j++)
			for(size_t i = 0; i < final.size(); i++)
				if (final[j][y] == final[i][y] && j != i)
					return false;
	return true;
}

bool	Random::checkUsedTo(std::vector<std::vector<std::string> > group, int n, std::string name) {
	if (!checkIsIn(name, usedTo))
		return false;
	for (size_t j = 0; j < group.size(); j++)
		if (!checkIsIn(group[j][n], usedTo))
			return true;
	return false;
}

bool	Random::checkGroup(std::vector<std::vector<std::string> > group, int n, std::string name) {
	for (size_t i = 0; i < group.size(); i++)
		if (name == group[i][n])
			return true;
	return false;
}

bool	Random::checkIsIn(std::string name, std::vector<std::string> list) {
	for (size_t i = 0; i < list.size(); i++)
		if (name == list[i])
			return true;
	return false;
}

std::string	Random::trim_non_alpha(const std::string& s) {
	size_t start = 0;
	size_t end = s.length();

	while (start < end && !std::isalpha(s[start]))
		++start;
	while (end > start && !std::isalpha(s[end - 1]))
		--end;
	return s.substr(start, end - start);
}

std::vector<std::string>	Random::ft_split(const std::string& str, char delimiter) {
	std::vector<std::string> result;
	size_t start = 0;

	while (start < str.length()) {
		while (start < str.length() && str[start] == delimiter)
			++start;
		if (start >= str.length())
			break;
		size_t end = start;
		while (end < str.length() && str[end] != delimiter)
			++end;
		std::string token = str.substr(start, end - start);
		token = trim_non_alpha(token);
		if (!token.empty())
			result.push_back(token);
		start = end;
	}
	return result;
}

std::vector<std::vector<std::string> >	Random::getFinal() {
	return final;
}