#ifndef MENU_HPP
	#define MENU_HPP

	#include <iostream>
	#include <cstdlib>
	#include <string>
	#include <iomanip>
	#include "Random.hpp"

	class Random;

class Menu {
private:
	Random	*list = NULL;
	void	random();
	void	manual();
	void	addUser();
	void	basicEng();
	void	basicIta();
	void	bonusIta();
	void	bonusEng();
	void	taskList();
	void	printTask();
	void	addUsedto();
	void	clearScreen();
	void	printManual();
	void	questionEng();
	void	questionIta();
	void	mandatoryEng();
	void	mandatoryIta();
	void	printMainMenu();
	void	groupCreation();
	void	printGuideIndex();
	void	showGitHubGuide();
	void	collaboratorsEng();
	void	collaboratorsIta();
	void	printByColumns(const std::vector<std::vector<std::string> >& data);
	bool	equalsIgnoreCase(const std::string& a, const std::string& b);

	std::string	trim_space(const std::string& s);
	std::string	trim_non_alpha(const std::string& s);

public:
	void	run();
};

#endif