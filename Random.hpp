#ifndef RANDOM_HPP
	#define RANDOM_HPP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <cstdlib>
	#include <ctime>

class Random {
private:
	std::vector<std::vector<std::string> >	final;
	std::vector<std::string>				userList;
	std::vector<std::string>				usedTo;
	int										loop;

public:
	Random();
	~Random();
	Random(std::string list);

	void	randomize();
	bool	noLoop(int n);
	bool	addUser(std::string name);
	bool	addUsedTo(std::string name);

	void	plus(size_t &i, std::vector<std::string> arr);
	bool	checkScrumble();
	bool	checkIsIn(std::string name, std::vector<std::string> list);
	bool	checkGroup(std::vector<std::vector<std::string> > group, int n, std::string name);
	bool	checkUsedTo(std::vector<std::vector<std::string> > group, int n, std::string name);
	std::string								trim_non_alpha(const std::string& s);
	std::vector<std::string>				scrumble(std::vector<std::string> vector);
	std::vector<std::string>				ft_split(const std::string& str, char delimiter);
	std::vector<std::vector<std::string> >	getFinal();
};

#endif