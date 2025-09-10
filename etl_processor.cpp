#include <iostream>
#include "etl_processor.h"
#include "rapidjson/document.h"

void processEvents(const rapidjson::Document& doc) {
    if (!doc.IsArray()) {
        std::cerr << "Expected root JSON array for events." << std::endl;
        return;
    }

    for (rapidjson::SizeType i = 0; i < doc.Size(); ++i) {
        const auto& event = doc[i];
        if (!event.IsObject()) continue;

        std::string eventId = (event.HasMember("id") && event["id"].IsString())
                              ? event["id"].GetString() : "";

        std::string eventType = (event.HasMember("type") && event["type"].IsString())
                                ? event["type"].GetString() : "";

        std::string actorLogin = "N/A";
        if (event.HasMember("actor") && event["actor"].IsObject()) {
            const auto& actor = event["actor"];
            if (actor.HasMember("login") && actor["login"].IsString()) {
                actorLogin = actor["login"].GetString();
            }
        }

        std::string repoName = "N/A";
        if (event.HasMember("repo") && event["repo"].IsObject()) {
            const auto& repo = event["repo"];
            if (repo.HasMember("name") && repo["name"].IsString()) {
                repoName = repo["name"].GetString();
            }
        }

        int pushId = -1;
        if (eventType == "PushEvent" && event.HasMember("payload") && event["payload"].IsObject()) {
            const auto& payload = event["payload"];
            if (payload.HasMember("push_id") && payload["push_id"].IsInt()) {
                pushId = payload["push_id"].GetInt();
            }
        }

        std::cout << "EventID: " << eventId
                  << ", Type: " << eventType
                  << ", Actor: " << actorLogin
                  << ", Repo: " << repoName
                  << ", PushID: " << pushId << std::endl;
    }
}
