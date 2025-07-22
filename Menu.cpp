#include "Menu.hpp"

void Menu::run() {
	bool running = true;
	printMainMenu();
	while (running) {
		std::string choice;
		std::cout << "> ";
		if (!std::getline(std::cin, choice)) {
			std::cout << "\n[EOF rilevato. Uscita dal programma.]\n";
			if (list)
				delete list;
			break;
		}

		if (equalsIgnoreCase(trim_space(choice), "1"))
			groupCreation();
		else if (equalsIgnoreCase(trim_space(choice), "2"))
			addUser();
		else if (equalsIgnoreCase(trim_space(choice), "3"))
			addUsedto();
		else if (equalsIgnoreCase(trim_space(choice), "man"))
			manual();
		else if (equalsIgnoreCase(trim_space(choice), "task"))
			taskList();
		else if (equalsIgnoreCase(trim_space(choice), "random"))
			random();
		else if (equalsIgnoreCase(trim_space(choice), "EXIT")) {
			running = false;
			if (list)
				delete list;
		} else
			std::cout << "input non valido...\n" << std::endl;
	}

	std::cout << "Programma terminato.\n";
}

void	Menu::printMainMenu() {
	clearScreen();
	std::cout << "========= MENU PRINCIPALE =========" << std::endl;
	std::cout << "1.      Crea gruppo di utenti" << std::endl;
	std::cout << "2.      Aggiungi uno user" << std::endl;
	std::cout << "3.      Aggiungi uno usedto" << std::endl;
	std::cout << "man.    Manuale di sopravvivenza" << std::endl;
	std::cout << "task.   task per la giornata" << std::endl;
	std::cout << "random. Aggiungi uno usedto" << std::endl;
	std::cout << "EXIT. per uscire" << std::endl;
}

void	Menu::groupCreation() {
	clearScreen();
	std::cout << "========= CREAZIONE GRUPPO UTENTI =========" << std::endl;
	std::cout << "(EXIT per tornare al Menu)" << std::endl;
	std::cout << "Inserisci lista degli user per creare il gruppo" << std::endl;
	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		if (equalsIgnoreCase(trim_space(input), "EXIT")) {
			break;
		} else if (trim_space(input) != "") {
			if (list)
				delete list;
			list = new Random(input); 
			std::cout << "Hai creato un nuvo gruppo!!\n" << std::endl;
		} else 
			std::cout << "inserire membri per il gruppo\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::addUser() {
	clearScreen();
	std::cout << "========= AGGIUNTA DI UN USER =========" << std::endl;
	std::cout << "(EXIT per tornare al Menu)" << std::endl;
	std::cout << "inserisci nuovo user da aggiungere al gruppo" << std::endl;
	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		if (equalsIgnoreCase(trim_space(input), "EXIT"))
			break;
		if (list) {
			if (list->addUser(input)) {
				std::cout << "Hai aggiunto l'utente: " << input << "!\n" << std::endl;
			} else if (trim_space(input) == "") {
				std::cout << "Fornire un utente da aggiungere...\n" << std::endl;
			} else
				std::cout << "L'utente è già presente nel gruppo o inadatto...\n" << std::endl;
		} else
			std::cout << "nessuna lista esistente\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::addUsedto() {
	clearScreen();
	std::cout << "========= AGGIUNTA DI UNO USEDTO =========" << std::endl;
	std::cout << "(EXIT per tornare al Menu)" << std::endl;
	std::cout << "Lo usedTo è chi conosce già github" << std::endl;
	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		if (equalsIgnoreCase(trim_space(input), "EXIT"))
			break;
		if (list) {
			if (list->addUsedTo(input)) {
				std::cout << "Hai aggiunto lo usedto: " << input << "!\n" << std::endl;
			} else if (trim_space(input) == "") {
				std::cout << "Fornire uno usedTo da aggiungere...\n" << std::endl;
			} else
				std::cout << "Lo usedTo è già presente nel gruppo o inadatto...\n" << std::endl;
		} else
			std::cout << "nessuna lista esistente\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::random() {
	clearScreen();
	if (!list)
		return ;
	std::string input;
	std::cout << "========= RANDOMIZER =========" << std::endl;
	std::cout << "(EXIT per tornare al Menu)" << std::endl;
	std::cout << "random. per avere gli utenti randomizzati" << std::endl;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		if (equalsIgnoreCase(trim_space(input), "EXIT")) {
			break;
		} else if (equalsIgnoreCase(trim_space(input), "random")){
			std::cout << "scrumbling in corso, attendere...\n";
			list->randomize();
			printByColumns(list->getFinal());
		} else
			std::cout << "input non valido...\n" << std::endl;
	}
	printMainMenu();
}

std::string	Menu::trim_non_alpha(const std::string& s) {
	size_t start = 0;
	size_t end = s.length();

	while (start < end && !std::isalpha(s[start]))
		++start;
	while (end > start && !std::isalpha(s[end - 1]))
		--end;
	return s.substr(start, end - start);
}

std::string	Menu::trim_space(const std::string& s) {
	size_t start = 0;
	size_t end = s.length();

	while (start < end && s[start] == ' ')
		++start;
	while (end > start && s[end - 1] == ' ')
		--end;
	return s.substr(start, end - start);
}

void	Menu::printByColumns(const std::vector<std::vector<std::string> > &data) {
	if (data.empty())
		return;

	std::vector<size_t> columnWidths(data.size(), 0);
	for (size_t col = 0; col < data.size(); ++col) {
		for (size_t row = 0; row < data[col].size(); ++row) {
			if (data[col][row].length() > columnWidths[col])
				columnWidths[col] = data[col][row].length();
		}
	}

	for (size_t row = 0; row < data[0].size(); ++row) {
		for (size_t col = 0; col < data.size(); ++col) {
			std::cout << std::left << std::setw(columnWidths[col] + 4) << data[col][row];
		}
		std::cout << std::endl;
	}
}

bool	Menu::equalsIgnoreCase(const std::string& a, const std::string& b) {
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

void	Menu::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}


void	Menu::manual() {
	clearScreen();
	printManual();

	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF rilevato. Ritorno al Menu principale.]\n";
			std::cin.clear();
			break;
		}
		input = trim_space(input);

		if (equalsIgnoreCase(input, "EXIT"))
			break;
		else if (equalsIgnoreCase(input, "1"))
			basicIta();
		else if (equalsIgnoreCase(input, "2"))
			collaboratorsIta();
		else if (equalsIgnoreCase(input, "3"))
			basicEng();
		else if (equalsIgnoreCase(input, "4"))
			collaboratorsEng();
		else
			std::cout << "Selezione non valida.\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::printManual() {
	std::cout << "========= MANUALE GITHUB =========" << std::endl;
	std::cout << "1. Uso base di GitHub(it)" << std::endl;
	std::cout << "2. Aggiungere collaboratori a una repository(it)" << std::endl;
	std::cout << std::endl;
	std::cout << "3. Basic GitHub usage(en)" << std::endl;
	std::cout << "4. Adding collaborators to a repository(en)" << std::endl;
	std::cout << "EXIT. Torna al menu principale" << std::endl;
}

void	Menu::basicIta() {
	clearScreen();
	std::cout << "========= MANUALE DI SOPPRAVIVENZA PER GITHUB =========" << std::endl;
	std::cout << "1. Crea un account su https://github.com:" << std::endl;
	std::cout << "   utilizza per l'account l'email che preferisci" << std::endl;
	std::cout << "   e come nome utente metti il tuo nome intra." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Una volta nella home premi il tasto \"NEW\"" << std::endl;
	std::cout << "   per creare una nuova repository, decidi" << std::endl;
	std::cout << "   il nome delal repository e mettila come" << std::endl;
	std::cout << "   \"Public\", ricordati che questo è solo" << std::endl;
	std::cout << "   una guida! Va dare un'occhiata a che" << std::endl;
	std::cout << "   differenza c'è tra public e private." << std::endl;
	std::cout << std::endl;
	std::cout << "3. aggiungi la tua chiave ssh andando nei settings." << std::endl;
	std::cout << "   Dopo shell00 dovreste essere abbastanza pratici" << std::endl;
	std::cout << "   quindi no starò a spiegarvi come si fa ;)." << std::endl;
	std::cout << std::endl;
	std::cout << "4. Clona il repository sul tuo computer:" << std::endl;
	std::cout << "   git clone \"link alla tua repositori\"..." << std::endl;
	std::cout << "   il link si trova della pagina della repository" << std::endl;
	std::cout << "   premento il pulsante \"code <>\"." << std::endl;
	std::cout << std::endl;
	std::cout << "5. Aggiungi I file alla cartella clonata e pushali" << std::endl;
	std::cout << "   sulla repository." << std::endl;
	std::cout << "   git add . (guardate che cosa fa)" << std::endl;
	std::cout << "   git commit -m \"messaggio generico\"" << std::endl;
	std::cout << "   git push" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Premi INVIO per tornare al manuale...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printManual();
}

void	Menu::collaboratorsIta() {
	clearScreen();
	std::cout << "========= AGGIUNGERE COLLABORATORI =========" << std::endl;
	std::cout << "1. Vai alla repository su GitHub." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Clicca su 'Settings' del repository" << std::endl;
	std::cout << std::endl;
	std::cout << "3. Nel menu a sinistra, seleziona 'Collaborators'" << std::endl;
	std::cout << std::endl;
	std::cout << "4. Clicca 'Add people' e inserisci il nome utente GitHub" << std::endl;
	std::cout << std::endl;
	std::cout << "5. Il collaboratore riceverà un invito che dovrà accettare" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Premi INVIO per tornare al manuale...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printManual();
}

void	Menu::basicEng() {
	clearScreen();
	std::cout << "========= BASIC GITHUB USAGE =========" << std::endl;
	std::cout << "1. Create an account at https://github.com" << std::endl;
	std::cout << "   You can use any email you like." << std::endl;
	std::cout << "   For your username, use your Intra username." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Once on your dashboard, click \"NEW\"" << std::endl;
	std::cout << "   to create a new repository. Choose a name" << std::endl;
	std::cout << "   and set it as 'Public' for now." << std::endl;
	std::cout << "   (Tip: Learn the difference between public and private repos!)" << std::endl;
	std::cout << std::endl;
	std::cout << "3. Add your SSH key by going into your GitHub settings." << std::endl;
	std::cout << "   After completing shell00, you should be familiar enough" << std::endl;
	std::cout << "   with it, so I won't bother explaining how to do it ;)." << std::endl;
	std::cout << std::endl;
	std::cout << "4. Clone the repository to your computer:" << std::endl;
	std::cout << "   git clone <your repository link>" << std::endl;
	std::cout << "   You can find the link by clicking the green \"Code <>\" button." << std::endl;
	std::cout << std::endl;
	std::cout << "5. Add files to the cloned folder and push them:" << std::endl;
	std::cout << "   git add . (go search what it do)" << std::endl;
	std::cout << "   git commit -m \"your message here\"" << std::endl;
	std::cout << "   git push" << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the guide...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printManual();
}

void	Menu::collaboratorsEng() {
	clearScreen();
	std::cout << "========= ADDING COLLABORATORS =========" << std::endl;
	std::cout << "1. Go to your repository on GitHub." << std::endl;
	std::cout << std::endl;
	std::cout << "2. Click on 'Settings' at the top of the repository page." << std::endl;
	std::cout << std::endl;
	std::cout << "3. In the left sidebar, choose 'Collaborators'." << std::endl;
	std::cout << std::endl;
	std::cout << "4. Click 'Add people' and enter the GitHub username." << std::endl;
	std::cout << std::endl;
	std::cout << "5. The person will receive an invitation they must accept." << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the guide...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printManual();
}

void	Menu::taskList() {
	clearScreen();
	printTask();

	std::string input;
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin, input)) {
			std::cout << "\n[EOF detected. Returning to main menu.]\n";
			std::cin.clear();
			break;
		}
		input = trim_space(input);

		if (equalsIgnoreCase(input, "EXIT"))
			break;
		else if (equalsIgnoreCase(input, "1"))
			mandatoryIta();
		else if (equalsIgnoreCase(input, "2"))
			bonusIta();
		else if (equalsIgnoreCase(input, "3"))
			questionIta();
		else if (equalsIgnoreCase(input, "4"))
			mandatoryEng();
		else if (equalsIgnoreCase(input, "5"))
			bonusEng();
		else if (equalsIgnoreCase(input, "6"))
			questionEng();
		else
			std::cout << "input non valido\n" << std::endl;
	}
	printMainMenu();
}

void	Menu::printTask() {
	std::cout << "========= TASK LIST =========" << std::endl;
	std::cout << "1. Mandatory task(it)" << std::endl;
	std::cout << "2. Bonus(it)" << std::endl;
	std::cout << "3. Question(it)" << std::endl;
	std::cout << std::endl;
	std::cout << "4. Mandatory task(en)" << std::endl;
	std::cout << "5. Bonus(en)" << std::endl;
	std::cout << "6. Question(en)" << std::endl;
	std::cout << "EXIT. ritorna al main menu" << std::endl;
}

void	Menu::mandatoryIta() {
	clearScreen();
	std::cout << "========= MANDATORY =========" << std::endl;
	std::cout << "E' il momento di imparare ad usare git hub e lasicare in pace" << std::endl;
	std::cout << "questi poveri baywatcher. per prima cosa dovrete creare una" << std::endl;
	std::cout << "vostra repository su gitHUB, per poi scrivere l'inizio di una" << std::endl;
	std::cout << "storia da voi inventata. dopo aver pushato il primo pezzo di" << std::endl;
	std::cout << "storia dovrete trovare il vostro prossimo peer così da aggiungerlo" << std::endl;
	std::cout << "come collaboratore alla vostra repository. a quel punto sarà lui" << std::endl;
	std::cout << "a dover clonare la repo, leggere il vostro pezzo di storia" << std::endl;
	std::cout << "per poi continuarlo. Di nuovo dovrete aggiungere il " << std::endl;
	std::cout << "vostro prossimo peer e ripetere la stessa operazione. Questa" << std::endl;
	std::cout << "volta dovrà scrivere una parte conclusiva dei primi due pezzi" << std::endl;
	std::cout << "di storia presenti sulla repository." << std::endl;
	std::cout << "Per finire in tutte le vostre repository dovrete aggiungere" << std::endl;
	std::cout << "anche un membro dello staff o baywatcher così che possa leggere" << std::endl;
	std::cout << "le vostre storie e proclamare un vincitore!" << std::endl;
	std::cout << "I tre vincitory vincitori vinceranno un achivment esclusivo" << std::endl;
	std::cout << "'Story teller', sempre che lo staff me lo permetta..." << std::endl;
	std::cout << "Cmq, come sempre, ricordatevi che quello che conta di più" << std::endl;
	std::cout << "è divertirsi come dei pazzi! Quindi scrivete le storie più" << std::endl;
	std::cout << "assurde che vi vengono in mente!" << std::endl;
	std::cout << std::endl;
	std::cout << "premere ENTER per tornare alal task list...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printTask();
}

void	Menu::bonusIta() {
	clearScreen();
	std::cout << "========= BONUS =========" << std::endl;
	std::cout << "Non mi dilungherò visto che ho usato quasi tutte le mie" << std::endl;
	std::cout << "facoltà celebrali per la mandatory part. Visto che questa" << std::endl;
	std::cout << "questa è un'attività per imparare ad usare github mi sembrava" << std::endl;
	std::cout << "giusto provare a farvi fare anche questo(non ho voglia di" << std::endl;
	std::cout << "correggere questa parte quindi vedete di fare solo la parte" << std::endl;
	std::cout << "mardatory intesi!)... per i coraggiosi che volessero inoltrarsi" << std::endl;
	std::cout << "in questo mondo di caos e disperazione provate pure a mettere" << std::endl;
	std::cout << "ogni pezzo della storia in una branch separata. Il primo pezzo" << std::endl;
	std::cout << "nel main, la seconda una branch chiamata second e la terza in" << std::endl;
	std::cout << "third(vi prego non fatelo, manco io ho ancora capito come" << std::endl;
	std::cout << "funzionano...). Il premio per i pochi eletti che faranno" << std::endl;
	std::cout << "questa pazzia verrà deciso in seguito, sperando che nessuno" << std::endl;
	std::cout << "lo faccia in parte..." << std::endl;
	std::cout << std::endl;
	std::cout << "premere ENTER per tornare alal task list...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printTask();
}

void	Menu::questionIta() {
	clearScreen();
	std::cout << "========= QUESTION =========" << std::endl;
	std::cout << "1.  Come capisco quali sono i miei peer?" << std::endl;
	std::cout << "    Vi verrà data una 'tabella', una volta trovato il" << std::endl;
	std::cout << "    vostro nome, sulla stessa riga troverete la priam e la" << std::endl;
	std::cout << "    seconda persona da agguingere alla vostra repo. per" << std::endl;
	std::cout << "    esempio, se sei topiana trovi la riga 'topiana fde-sant alborghi'." << std::endl;
	std::cout << "    dovrai aggiungere prima fde-sant e poi alborghi, semplice no?" << std::endl;
	std::cout << std::endl;
	std::cout << "2.  Ma per repo si intende repository?" << std::endl;
	std::cout << "    Si ragazzi, SI!!!" << std::endl;
	std::cout << std::endl;
	std::cout << "premere ENTER per tornare alal task list...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printTask();
}

void Menu::mandatoryEng() {
	clearScreen();
	std::cout << "========= MANDATORY =========" << std::endl;
	std::cout << "It's time to learn how to use GitHub and finally leave" << std::endl;
	std::cout << "those poor baywatchers alone. First, you'll have to create" << std::endl;
	std::cout << "your own repository on GitHub, then write the beginning of a" << std::endl;
	std::cout << "story you invent yourself. After pushing the first part of the" << std::endl;
	std::cout << "story, you must find your next peer and add them" << std::endl;
	std::cout << "as a collaborator to your repository. At that point, they will" << std::endl;
	std::cout << "have to clone your repo, read your part of the story," << std::endl;
	std::cout << "and then continue it. Then again, you'll add the" << std::endl;
	std::cout << "next peer and repeat the process. This time, they will" << std::endl;
	std::cout << "write a final part that concludes the two previous" << std::endl;
	std::cout << "sections of the story already in the repository." << std::endl;
	std::cout << "Finally, you must also add a member of the staff" << std::endl;
	std::cout << "or a baywatcher to your repository so they can read" << std::endl;
	std::cout << "your stories and choose a winner!" << std::endl;
	std::cout << "The three winners will earn the exclusive achivment" << std::endl;
	std::cout << "'Story Teller' – assuming the staff lets me do it..." << std::endl;
	std::cout << "Anyway, as always, remember that what matters most" << std::endl;
	std::cout << "is to have a blast! So write the wildest stories" << std::endl;
	std::cout << "you can think of!" << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the task list...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printTask();
}

void Menu::bonusEng() {
	clearScreen();
	std::cout << "========= BONUS =========" << std::endl;
	std::cout << "I won’t go into too much detail since I used up almost all my" << std::endl;
	std::cout << "brainpower on the mandatory part. Since this activity is" << std::endl;
	std::cout << "meant to teach you GitHub, I thought it would be fair" << std::endl;
	std::cout << "to challenge you with this as well (though I won’t be" << std::endl;
	std::cout << "correcting this part, so please just stick to the mandatory" << std::endl;
	std::cout << "part, got it?)... For the brave ones who want to dive" << std::endl;
	std::cout << "into this world of chaos and despair, try putting" << std::endl;
	std::cout << "each part of the story into a separate branch. The first" << std::endl;
	std::cout << "part in `main`, the second in a branch called `second`, and" << std::endl;
	std::cout << "the third in `third` (please don’t actually do this, not even I" << std::endl;
	std::cout << "fully understand how this works...). The reward for the few" << std::endl;
	std::cout << "chosen ones who go through with this madness will be" << std::endl;
	std::cout << "decided later – hopefully no one actually does it..." << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the task list...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printTask();
}

void	Menu::questionEng() {
	clearScreen();
	std::cout << "========= QUESTIONS =========" << std::endl;
	std::cout << "1.  How do I know who my peers are?" << std::endl;
	std::cout << "    You will be given a 'table'. Once you find your" << std::endl;
	std::cout << "    name in it, on the same row you'll see the first and" << std::endl;
	std::cout << "    second person to add to your repo." << std::endl;
	std::cout << "    For example, if your name is 'topiana' and you see the line:" << std::endl;
	std::cout << "    'topiana fde-sant alborghi', it means you must add" << std::endl;
	std::cout << "    fde-sant first, then alborghi. Simple, right?" << std::endl;
	std::cout << std::endl;
	std::cout << "2.  Wait... does 'repo' mean 'repository'?" << std::endl;
	std::cout << "    Yes guys, YES!!!" << std::endl;
	std::cout << std::endl;
	std::cout << "Press ENTER to return to the task list...";
	std::string dummy;
	std::getline(std::cin, dummy);
	clearScreen();
	printTask();
}