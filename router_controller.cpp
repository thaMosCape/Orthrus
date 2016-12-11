#include "router_controller.hpp"



using namespace Orthrus;


RouterController::RouterController(std::string hostname, unsigned short local_port)
	: router(io_service, hostname, local_port)
{}


void RouterController::start(void) try
{ 
	routerThread.reset(new std::thread(&RouterController::run, this)); 
}
catch (std::exception& e) { error_handler(e); }


void RouterController::stop(void) try
{
    io_service->stop();
    router.stop();
    if (routerThread.get())
    	routerThread->join(); 
}
catch (std::exception& e) { error_handler(e); }


void RouterController::run(void) try
{   
    router.start();
    io_service->run();
}
catch (std::exception& e) { error_handler(e); }


void RouterController::connect(std::string host, std::string port) try
{
	router.connect(host+':'+port);
}
catch (std::exception& e) { error_handler(e); }


void RouterController::set_error_handler(error_handler_t&& eh) try
{ 
	error_handler = eh; 
	router.set_error_handler(error_handler);
}
catch (std::exception& e) { error_handler(e); }
