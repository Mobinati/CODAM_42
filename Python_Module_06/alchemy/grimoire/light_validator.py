from .light_spellbook import light_spell_allowed_ingredients


def validate_ingredients(ingredients: str) -> str:
    allowed = light_spell_allowed_ingredients()
    for ing in allowed:
        if ing.lower() in ingredients.lower():
            return ("VALID")
    return ("INVALID")
