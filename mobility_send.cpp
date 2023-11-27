

// ecs36b mobility_client program

#include <iostream>
#include "ecs36b_Common.h"
#include "ecs36b_Exception.h"

// JSON RPC part
#include "mobility_client.h"
#include "Message.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int
main()
{
  SP_Person instructor { "Felix" };
  
  SP_Person student01  { "Tome" };
  SP_Person student02  { "Jerry" };

  std::string my_team_name = "midterm_5";
  
  Team my_team;
  my_team.setName(my_team_name);      
  my_team.addAMember(student01);
  my_team.addAMember(student02);
  
  Message m {my_team, instructor};
  Json::Value jv_content;
  jv_content["header"] = "midterm 5 on December 8, 2023";
  jv_content["body"] = "ecs36b Exception tutorial available";
  m.content = jv_content;

  Json::Value jv_message = m.dump2JSON();
  std::cout << jv_message.toStyledString() << std::endl;

  // okay, going for the server
  // HttpClient httpclient("https://40b8-2601-200-c000-39f0-616c-7ba7-6e23-e672.ngrok-free.app");
  // replace here with the ngrok link
  
  HttpClient httpclient("http://127.0.0.1:8384"); // replace here with the ngrok link
  mobility_Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  Json::Value exception_json;

  try {
    myv = myClient.send("send", "Message1", jv_message, my_team_name);
    if ((myv["status"]).isNull())
      {
	exception_json["status"] = "failed";
	exception_json["reason"] = "RPC response without status";
	throw ecs36b_Exception { exception_json };
      }
    else
      {
	if ((myv["status"]).asString() == "failed")
	  {
	    throw ecs36b_Exception { myv };
	  }
      }
  } catch (ecs36b_Exception &e) {
    cerr << e.what() << endl;
    std::cout << e.exp_msg << std::endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  return 0;
}
