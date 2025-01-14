////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
////////////////////////////////////////////////////////////////////////////////

#include "RestPleaseUpgradeHandler.h"

#include <velocypack/StringRef.h>

using namespace arangodb;
using velocypack::StringRef;

RestPleaseUpgradeHandler::RestPleaseUpgradeHandler(GeneralRequest* request,
                                                   GeneralResponse* response)
    : RestHandler(request, response) {}

RestStatus RestPleaseUpgradeHandler::execute() {
  resetResponse(rest::ResponseCode::OK);
  
  _response->setContentType(rest::ContentType::TEXT);
  _response->addRawPayload(StringRef("Database: "));
  _response->addRawPayload(StringRef(_request->databaseName()));
  _response->addRawPayload(StringRef("\r\n\r\n"));
  _response->addRawPayload(StringRef("It appears that your database must be upgraded. "));
  _response->addRawPayload(StringRef("Normally this can be done using\r\n\r\n"));
  _response->addRawPayload(StringRef("  /etc/init.d/arangodb3 stop\r\n"));
  _response->addRawPayload(StringRef("  /etc/init.d/arangodb3 upgrade\r\n"));
  _response->addRawPayload(StringRef("  /etc/init.d/arangodb3 start\r\n\r\n"));
  _response->addRawPayload(StringRef("Please check the log file for details.\r\n"));

  return RestStatus::DONE;
}
