using UnityEngine;

public class MachineBase : MonoBehaviour
{
    [Header("Paramètres")]
    public string machineName;
    public float maxHealth = 100f;
    private float currentHealth;

    [Header("Inventaire")]
    public int inventorySize = 10;
    // Liste d'items (ton système de classe Item)
    // public List<Item> inventory; 

    [Header("Ports (IO)")]
    public int inputCount;  // Défini à la pose ou via le ScriptableObject
    public bool hasOutput;

    void Start()
    {
        currentHealth = maxHealth;
        SetupVisual();
    }

    void SetupVisual()
    {
        // On s'assure qu'il y a un cube visuel
        GameObject visual = GameObject.CreatePrimitive(PrimitiveType.Cube);
        visual.transform.SetParent(this.transform);
        visual.transform.localPosition = Vector3.zero;
    }

    public void TakeDamage(float amount)
    {
        currentHealth -= amount;
        if (currentHealth <= 0) Die();
    }

    void Die()
    {
        // Logique de destruction/recyclage
        Destroy(gameObject);
    }

    // Méthode de traitement (à appeler via Coroutine ou Update)
    public virtual void Process()
    {
        // Logique de transformation des entrées vers la sortie
    }
}