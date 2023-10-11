//
//  luaosutils_os.h
//  luaosutils
//
//  Created by Robert Patterson on 9/9/22.
//  Copyright © 2022 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#ifndef luaosutils_os_h
#define luaosutils_os_h

#include <memory>
#include <map>

namespace luaosutils
{

using lua_callback = std::function<void (bool, const std::string&)>;
using HeadersMap = std::map<std::string, std::string>;

static const int kHTTPStatusCodeOK = 200;

#if OPERATING_SYSTEM == MAC_OS
using OSSESSION_ptr = void*;
#endif //OPERATING_SYSTEM == MAC_OS

#if OPERATING_SYSTEM == WINDOWS
#include <wininet.h>

enum class win_request_state
{
   SEND,
   ALLOCATE,
   READ_CHUNK,
   CHUNK_COMPLETE,
   TERMINATE,
   COMPLETE
};

struct win_request_context
{
   win_request_state state;
   lua_callback callbackFunction;
   HINTERNET hInternet{};
   HINTERNET hConnect{};
   HINTERNET hRequest{};
   HANDLE hEvent{};
   DWORD statusCode{};
   DWORD readErrorCode{};
   LONG bufferReserve{};
   std::string buffer{};
   std::string postData{};
   std::vector<CHAR> readBuf{};
   DWORD numBytesRead{};
   
   win_request_context(lua_callback callback);
   ~win_request_context();
   
   static win_request_context* get_context_from_timer(UINT_PTR timerID);
   
   UINT_PTR get_timer_id() const { return timerID; }
   bool set_timer_id(UINT_PTR id);
   
private:
   UINT_PTR timerID{};
   
   static std::map<UINT_PTR, win_request_context*>& getTimerMap()
   {
      static std::map<UINT_PTR, win_request_context*> timerMap;
      return timerMap;
   }
};
using OSSESSION_ptr = std::shared_ptr<win_request_context>;
#endif //OPERATING_SYSTEM == WINDOWS

OSSESSION_ptr https_request(const std::string& requestType, const std::string &urlString, const std::string& postData,
                            const HeadersMap& headers, double timeout, lua_callback callback);
#if OPERATING_SYSTEM == MAC_OS
void cancel_session(OSSESSION_ptr session);
#endif

void error_message_box(const std::string &msg);

std::string server_name(const std::string &url);

}

#endif /* luaosutils_os_h */
