/**
 * Copyright (C) 2019 WerWolv
 * 
 * This file is part of EdiZon.
 * 
 * EdiZon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * EdiZon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with EdiZon.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <edizon.hpp>

#include "save/title.hpp"
#include "save/account.hpp"
#include "helpers/folder.hpp"

namespace edz::save {

    class SaveManager {
    public:
        static EResult backup(Title *title, Account *account, std::string backupName);
        static EResult restore(Title *title, Account *account, std::string backupName);
 
        static EResult swapSaveData(Title *title, Account *account, std::string backupName);
        static EResult swapSaveData(Title *title, Account *account1, Account *account2);
        static EResult duplicate(Title *title, Account *from, Account *to);
 
        static EResult upload(Title *title, Account *account);
        static EResult upload(Title *title, std::string backupName);
 
        static EResult download(Title *title, Account *account);
        static EResult download(Title *title, std::string backupName);
 
        static std::pair<EResult, std::vector<std::string>> getLocalBackupList(Title *title);
        static std::pair<EResult, std::vector<std::string>> getOnlineBackupList(Title *title);
        static std::pair<EResult, bool> areBackupsUpToDate(Title *title, Account *account);
        
    private:
    };

}
