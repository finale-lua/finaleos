//
//  luaosutils_text_os.h
//  luaosutils-static
//
//  Created by Robert Patterson on 2/27/23.
//  Copyright © 2023 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#ifndef luaosutils_text_os_h
#define luaosutils_text_os_h

bool text_convert_encoding(const std::string& text, unsigned int fromCodepage, std::string& output, unsigned int toCodepage);


#endif /* luaosutils_text_os_h */
