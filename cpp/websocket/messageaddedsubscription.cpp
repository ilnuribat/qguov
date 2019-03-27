#include "messageaddedsubscription.h"

MessageAddedSubscription::MessageAddedSubscription(GlobalStore *globalStore): m_globalStore(globalStore)
{
  query = R"(
            subscription {
              messageAdded {
                id
                text
                from {
                  id
                  initials
                  icon
                }
                to {
                  ... on Direct {
                    id
                  }
                  ... on Task {
                    id
                    name
                  }
                  __typename
                }
                createdAt
              }
            }
          )";
}

QString MessageAddedSubscription::getQuery() const {
  return query;
}
